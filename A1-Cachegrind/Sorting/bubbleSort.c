// C program for implementation of Bubble sort 
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

// A function to implement bubble sort
void bubbleSort(long int *arr, int N)
{
	for (int i = 0; i < N - 1; i++)

		// Last i elements are already in place
		for (int j = 0; j < N - i - 1; j++)
			if (arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
}


/* Function to print an array */
void printArray(long int *arr, int N)
{
	int i;
	for (int i = 0; i < N; i++)
		printf("%ld ", arr[i]);
	printf("\n");
}

// Driver program to test above functions
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
        bubbleSort(arr, elements_no);
        // printf("Sorted array: \n");
        // printArray(arr, elements_no);
        return 0;
    }
}
