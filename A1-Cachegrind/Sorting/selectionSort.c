// C program for implementation of selection sort
// Some of the code snippets are referred from Geeksforgeeks
#include <stdio.h>
#include <stdlib.h>

// Swap elements a and b
void swap(long int* a, long int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void selectionSort(long int *arr, int N)
{
	int min_index;

	// One by one move boundary of unsorted subarray
	for (int i = 0; i < N-1; i++)
	{
		// Find the minimum element in unsorted array
		min_index = i;
		for (int j = i+1; j < N; j++)
		if (arr[min_index] > arr[j])
			min_index = j;

		// Swap the found minimum element with the first element
		if(min_index != i)
			swap(&arr[min_index], &arr[i]);
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
        printf("Error: Array length for sorting is not provided as an argument\n");
        return 0;
    }
    else if(argc>2){
        printf("Error: Number of arguments passed should be one\n");
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
        selectionSort(arr, elements_no);
        // printf("Sorted array: \n");
        // printArray(arr, elements_no);
        return 0;
    }
}
