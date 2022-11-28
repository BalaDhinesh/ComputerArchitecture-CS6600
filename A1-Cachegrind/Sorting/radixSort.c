// C program of Radix Sort
// Some of the code snippets are referred from Geeksforgeeks
#include <stdio.h>
#include <stdlib.h>

// A utility function to get maximum value in arr[]
int getMax(long int *arr, int n)
{
	int max = arr[0];		// assign to first value
	for (int i = 1; i < n; i++)
		if (arr[i] > max)
			max = arr[i];
	return max;
}

// Count sorting function
void countSort(long int *arr, int n, int exp)
{
	long int temp[n]; // temp array
	int count[10] = { 0 };  // length is zero because % operator with 10 can result in {0,1,...,9}

	// Store count of occurrences in count[]
	for (int i = 0; i < n; i++){
		count[(arr[i] / exp) % 10]++;

	}

	// Assign cumulative count sum
	for (int i = 1; i < 10; i++){
		count[i] += count[i - 1];
	}

	// assign in sorted order
	for (int i = n - 1; i >= 0; i--) {
		temp[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	// copy back the temp array to arr
	for (int i = 0; i < n; i++){
		arr[i] = temp[i];
	}
		

}


void radixSort(long int *arr, int n)
{
	// Find the maximum number to know number of digits
	int m = getMax(arr, n);

	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, n, exp);
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
        radixSort(arr, elements_no);
        // printf("Sorted array: \n");
        // printArray(arr, elements_no);
        return 0;
    }

	
}
