/* C program for Merge Sort */
// Some of the code snippets are referred from Geeksforgeeks
#include <stdio.h>
#include <stdlib.h>

void merge(long int *arr, int left_index, int middle_index, int right_index)
{
	int i, j, k;
	int left_N = middle_index - left_index + 1;   // Size of first subarray
	int right_N = right_index - middle_index;	  // Size of second subarray

	// Copy data to temp arrays left_subarr[] and right_subarr[] //
	long int left_subarr[left_N];
	for (i = 0; i < left_N; i++)
		left_subarr[i] = arr[left_index + i];
	long int right_subarr[right_N];
	for (j = 0; j < right_N; j++)
		right_subarr[j] = arr[middle_index + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0, j = 0, k = left_index; 
	while (i < left_N && j < right_N) {
		if (left_subarr[i] <= right_subarr[j]) {
			arr[k] = left_subarr[i];
			i++;
		}
		else {
			arr[k] = right_subarr[j];
			j++;
		}
		k++;
	}
	// Remaining left subarray elements if any
	while (i < left_N) {
		arr[k] = left_subarr[i];
		i++;
		k++;
	}
	// Remaining right subarray elements if any
	while (j < right_N) {
		arr[k] = right_subarr[j];
		j++;
		k++;
	}
}


void mergeSort(long int *arr, int left_index, int right_index)
{
	if (left_index < right_index) {
		// middle_index is the point where array is divided into two subarrays
		int middle_index = left_index + (right_index - left_index) / 2;

		// Sort first and second halves
		mergeSort(arr, left_index, middle_index);
		mergeSort(arr, middle_index + 1, right_index);

		// merge sorted subarrays
		merge(arr, left_index, middle_index, right_index);
	}
}

/* Function to print an array */
void printArray(long int *arr, int N)
{
	int i;
	for (int i = 0; i < N; i++)
		printf("%ld ", arr[i]);
	printf("\n");
}

int main(int argc, char** argv)
{
    if(argc==1){
        printf("Error: Array length for sorting is not provided as an argument");
        return 0;
    }
    else if(argc>2){
        printf("Error: Number of arguments passed is more than two");
        return 0;
    }
    else{
        int elements_no = atoi(argv[1]);
        long int* arr;
        arr = (long int*)malloc(elements_no * sizeof(long int));
        srand(0);
        for (int i = 0; i < elements_no; i++) {
            arr[i] = rand();
        }
        mergeSort(arr, 0, elements_no-1);
        // printf("Sorted array: \n");
        // printArray(arr, elements_no);
        return 0;
    }

	
}