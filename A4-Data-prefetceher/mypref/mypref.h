#include "champsim.h"

/* Convenient macros to extract out page ID and block ID from a given 64-bit address */
#define EXTRACT_PAGE_ID(addr)   ((addr) >> LOG2_PAGE_SIZE)              /* Extract the page ID */
#define EXTRACT_BLOCK_ID(addr)  (((addr) >> LOG2_BLOCK_SIZE) & 0x3f)    /* Extract the block ID within the page */
 
/* Minimum and maximum value of the block IDs */
#define BLOCK_ID_MIN    0
#define BLOCK_ID_MAX    ((PAGE_SIZE / BLOCK_SIZE) - 1)

/* The length of the buffer, i.e. 'K' as mentioned in the question */
/* Tweak this value accordingly */
#define BUFFER_LENGTH   5

/* Utility method to prepare the address to prefetch */
uint64_t prepare_prefetch_address(uint64_t page_id, uint32_t block_id) {
    return (page_id << LOG2_PAGE_SIZE) + (block_id << LOG2_BLOCK_SIZE);
}

/* NUM_CPUS is a pre-defined constant set to the number of cores to use in the simulation */
uint64_t prev_page_id[NUM_CPUS];    /* Store the IDs of the previous page, per prefetcher */

/* Returns True if the access is to the same page. False otherwise */
bool is_on_same_page(uint32_t cpu_id, uint64_t curr_page_id) {
    uint64_t tmp_prev_page_id = prev_page_id[cpu_id];   /* Temporarily store the value of previous page ID */
    prev_page_id[cpu_id] = curr_page_id;                /* Update the page ID of the latest page accessed */
    
    /* If previous page ID is same as the current page ID */
    if(curr_page_id == tmp_prev_page_id){
        // cout << "YES" << endl;
        return 1;
    }
    // cout << "NO" << endl;
    
    
    /* Nope, it's different. Return False */
    return 0;
}