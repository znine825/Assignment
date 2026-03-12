#include <stdio.h>
#include <stdlib.h> // for calloc()
#define NUM_DATA 20

void printArray(int array[], int size, int per_line) {
	for (int i = 0; i < NUM_DATA / per_line; i++) {
		for (int j = 0; j < per_line; j++) {
			printf("%5d", array[i * per_line + j]);
		}
		printf("\n");
	}
}

void _mergeSort(int array[], int temp_array[], int left, int right) {
	if (left == right) {
		return;
	}

	int i, j, k;
	int mid = (left + right) / 2;

	_mergeSort(array, temp_array, left, mid);
	_mergeSort(array, temp_array, mid + 1, right);

	for (i = left; i <= right; i++) {
		temp_array[i] = array[i];
	}

	for (i = left, j = mid + 1, k = left; k <= right; k++)
	{
		if ((i <= mid) && (j <= right)) {
			if (temp_array[i] < temp_array[j]) {
				array[k] = temp_array[i];
				i++;
			}
			else {
				array[k] = temp_array[j];
				j++;
			}
		}
		else if ((i <= mid) && (j > right)) {
			array[k] = temp_array[i];
			i++;
		}
		else if ((i > mid) && (j <= right)) {
			array[k] = temp_array[j];
			j++;
		}
	}
}

void mergeSort(int array[], int size) {

	int* tmp_array = (int*)calloc(size, sizeof(int));
	if (tmp_array == NULL)
	{
		printf("Error in creation of tmp_array (size = %d) in mergeSort() !!!\n");
		exit;
	}
	_mergeSort(array, tmp_array, 0, size - 1);
	free(tmp_array);
}


int main(void) {
	int data_array[NUM_DATA] = { 19, 17, 15, 13, 11, 9, 7, 5, 3, 1, 18, 16, 14, 12, 10, 8, 6, 4, 2, 0 };

	printf("Integer array before mergeSort:\n");
	printArray(data_array, NUM_DATA, 10);

	mergeSort(data_array, NUM_DATA);

	printf("\nInteger array after mergeSort:\n");
	printArray(data_array, NUM_DATA, 10);

	return 0;
}