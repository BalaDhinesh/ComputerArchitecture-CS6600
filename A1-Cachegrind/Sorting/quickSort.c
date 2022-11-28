/* C program of QuickSort */
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

// function which finds the partition position
int partition (long int *arr, int low, int high)
{
	int pivot = arr[high]; // setting high index value as pivot
	int i = (low - 1);     // store index - leftmost index - 1 

	for (int j = low; j < high; j++)
	{
		// If current element is smaller than the pivot
		if (arr[j] <= pivot)
		{
			i++; // increment store index 
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}


void quickSort(long int *arr, int low, int high)
{
	if (low < high)
	{
		int partition_index = partition(arr, low, high);

		// recursive call left of pivot 
		quickSort(arr, low, partition_index - 1);
		// recursive call left of pivot 
		quickSort(arr, partition_index + 1, high);
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
        quickSort(arr, 0, elements_no-1);
        // printf("Sorted array: \n");
        // printArray(arr, elements_no);
        return 0;
    }

	
}