#include "ooo_cpu.h"

#define GLOBAL_HISTORY_LENGTH 14
#define GLOBAL_HISTORY_MASK (1 << GLOBAL_HISTORY_LENGTH) - 1
int branch_history_vector[NUM_CPUS];

#define GS_HISTORY_TABLE_SIZE 16384
int gs_history_table[NUM_CPUS][GS_HISTORY_TABLE_SIZE];
int my_last_prediction[NUM_CPUS];

int my_last_taken[NUM_CPUS];    // tracks the previous branch results
int cf_t[NUM_CPUS];             // confidence factor for taken
int cf_nt[NUM_CPUS];            // confidence factor for not taken
#define limit 10                // limit for confidence factors
#define half_limit 5            
#define thresh 15               // threshold for always taken or not taken
int al_t[NUM_CPUS];             // variable to track always taken or not taken cases

void O3_CPU::initialize_branch_predictor()
{
  cout << "CPU " << cpu << " My branch predictor" << endl;

  branch_history_vector[cpu] = 0;
  my_last_prediction[cpu] = 0;
  my_last_taken[cpu] = 0;

  for (int i = 0; i < GS_HISTORY_TABLE_SIZE; i++)
    gs_history_table[cpu][i] = 4;
    
  // Initialization of variables
  for (int j = 0; j < NUM_CPUS; j++) {
  	cf_t[j] = 0;
  	cf_nt[j] = 0;
  	al_t[j] = 0;
  }
}

unsigned int gs_table_hash(uint64_t ip, int bh_vector)
{
  unsigned int hash = ip ^ (ip >> GLOBAL_HISTORY_LENGTH) ^ (ip >> (GLOBAL_HISTORY_LENGTH * 2)) ^ bh_vector;
  hash = hash % GS_HISTORY_TABLE_SIZE;

  // printf("%d\n", hash);

  return hash;
}

uint8_t O3_CPU::predict_branch(uint64_t ip, uint64_t predicted_target, uint8_t always_taken, uint8_t branch_type)
{
  int prediction = 1;

  int gs_hash = gs_table_hash(ip, branch_history_vector[cpu]);
  
  // If always taken enabled then prediction 1
  if (al_t[cpu] == thresh) {
  	prediction = 1;
  }
  // If always not taken enabled then prediction 0
  else if (al_t[cpu] == -thresh) {
  	prediction = 0;
  }
  // If hash table value is 6 / 7 - prediction 1
  else if (gs_history_table[cpu][gs_hash] >= 6) {
  	prediction = 1;
  }
  // Low confidence interval
  // Hash table values - 4 / 5
  else if ((gs_history_table[cpu][gs_hash] >= 4) && (gs_history_table[cpu][gs_hash] < 6)) {
    // Taking confidence factor for taken into consideration
  	if(cf_t[cpu] >= half_limit) {
  		prediction = 1;
  	}
  	else {
  		prediction = 0;
  	}
  }
  // Low confidence interval
  // Hash table values - 2 / 3
  else if ((gs_history_table[cpu][gs_hash] >= 2) && (gs_history_table[cpu][gs_hash] < 4)) {
    // Taking confidence factor for not taken into consideration
  	if(cf_nt[cpu] >= half_limit) {
  		prediction = 0;
  	}
  	else {
  		prediction = 1;
  	}
  }	
  // If hash table value is 0 / 1 - prediction 0
  else if(gs_history_table[cpu][gs_hash] < 2) {
  	prediction = 0;
  }
  
  // Tracking the predictions
  my_last_prediction[cpu] = prediction;

  return prediction;
}

void O3_CPU::last_branch_result(uint64_t ip, uint64_t branch_target, uint8_t taken, uint8_t branch_type)
{
  int gs_hash = gs_table_hash(ip, branch_history_vector[cpu]);

  // correct_t signifies that the branch was predicted to be taken and it was indeed taken
  bool correct_t = (taken == 1) && (my_last_prediction[cpu] == 1);
  // correct_nt signifies that the branch was predicted to be not taken and it was indeed not taken
  bool correct_nt = (taken == 0) && (my_last_prediction[cpu] == 0);

  // Comparing always taken to threshold and updating accordingly
  // If continuously the branch is taken or not taken threshold number of times then it is enabled
  if ((al_t[cpu] < thresh) && (taken == 1)) {
    if (my_last_taken[cpu] == taken) {
      al_t[cpu]++;
    }
    else 
      al_t[cpu] = 0;
  }
  else if ((al_t[cpu] > -thresh) && (taken == 0)){
  	if (my_last_taken[cpu] == taken) {
      al_t[cpu]--;
    }
    else 
      al_t[cpu] = 0;
  }
  

  if (correct_t) {
  	if(cf_t[cpu] < limit)
      cf_t[cpu]++;          // Updating confidence factor for taken as the prediction was previously correct
  	if ((cf_t[cpu] == limit) && (gs_history_table[cpu][gs_hash] < 7)) {
  		gs_history_table[cpu][gs_hash]++;       // Updating hash table value
  	}
  }
  else if (correct_nt) {
    if(cf_nt[cpu] < limit)
  	  cf_nt[cpu]++;         // Updating confidence factor for not taken as the prediction was previously correct
  	if ((cf_nt[cpu] == limit) && (gs_history_table[cpu][gs_hash] > 0)) {
  		gs_history_table[cpu][gs_hash]--;       // Updating hash table value
  	}
  }
  // Mispredictions
  // Branch was predicted to be taken but actually it was not taken 
  // So confidence factor for taken is reduced and hash table value updated
  else if ((taken == 0) && (my_last_prediction[cpu] == 1)) {
    if(cf_t[cpu] > 0)
  	  cf_t[cpu]--;
    if ((gs_history_table[cpu][gs_hash] > 0)) {
  		gs_history_table[cpu][gs_hash]--;
  	}
  }
  // Branch was predicted to be not taken but actually it was taken 
  // So confidence factor for not taken is reduced and hash table value updated
  else if ((taken == 1) && (my_last_prediction[cpu] == 0)) {
    if(cf_nt[cpu] > 0)
  	  cf_nt[cpu]--;
    if ((gs_history_table[cpu][gs_hash] < 7)) {
  		gs_history_table[cpu][gs_hash]++;
  	}
  }

  // Tracking previous results for enabling always taken or not taken variable
  my_last_taken[cpu] = taken;
  
  // update branch history vector
  branch_history_vector[cpu] <<= 1;
  branch_history_vector[cpu] &= GLOBAL_HISTORY_MASK;
  branch_history_vector[cpu] |= taken;
}
