#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shuffleBigArray(int* array, int size) {
	int temp, rand_index;
	unsigned int u_int30 = 0;
	for (int i = 0; i < size; i++)
	{
		u_int30 = ((long)rand() << 15) | rand();
		temp = u_int30 % size;
		if (i != temp)
		{
			rand_index = array[i];
			array[i] = array[temp];
			array[temp] = rand_index;
		}
	}
}


int* genBigRandArray(int bigRandSize, int base) {
	int* bigIntArray;
	bigIntArray = (int*)calloc(bigRandSize, sizeof(int));
	for (int i = 0; i < bigRandSize; i++)
	{
		bigIntArray[i] = i + base;
	}
	shuffleBigArray(bigIntArray, bigRandSize);

	return bigIntArray;
}

void printBigArraySample(int* BigArray, int size, int per_line, int sample_lines) {
	for (int i = 0; i < per_line; i++) {
		for (int j = 0; j < sample_lines; j++) {
			printf("%10d", BigArray[i * sample_lines + j]);
		}
		printf("\n");
	}
	printf("...\n");
	for (int i = per_line - 1; i >= 0; i--) {
		for (int j = sample_lines - 1; j >= 0; j--) {
			printf("%10d", BigArray[size - 1 - (i * sample_lines + j)]);
		}
		printf("\n");
	}
}
int findMinIndex(int* array, int s_index, int e_index) {

	int min = array[0];
	for (int i = s_index; i < e_index; i++) {
		if (array[i] < min) {
			min = array[i];
		}
	}
	return min;
}
void selectSort(int* array, int size) {
	for (int i = 0; i < size; i++) {
		int min = i;
		for (int j = i + 1; j < size; j++) {
			if (array[j] < array[min]) {
				min = j;
			}
		}
		int temp = array[i];
		array[i] = array[min];
		array[min] = temp;
	}
}



void insertSort(int* array, int size) {
	for (int i = 1; i < size; i++) {
		int key = array[i];
		int j = i - 1;

		while (j >= 0 && array[j] > key) {
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = key;
	}
}

void _mergeSort(int* array, int* temp_array, int left, int right) {
	if (left >= right) {
		return;
	}

	int i, j, k;
	int mid = (left + right) / 2;
	_mergeSort(array, temp_array, left, mid);
	_mergeSort(array, temp_array, mid + 1, right);

	for (k = left; k <= right; k++) {
		temp_array[k] = array[k];
	}

	i = left; j = mid + 1;
	for (k = left; k <= right; k++) {
		if ((i <= mid) && (j <= right)) {
			if (temp_array[i] < temp_array[j]) {
				array[k] = temp_array[i++];
			}
			else {
				array[k] = temp_array[j++];
			}
		}
		else if (i <= mid) {
			array[k] = temp_array[i++];
		}
		else if (j <= right) {
			array[k] = temp_array[j++];
		}
	}
}

void mergeSort(int* array, int size) {
	int* temp_array = (int*)calloc(size, sizeof(int));
	if (temp_array == NULL) {
		printf("Error in creation of temp_array!\n");
		exit;
	}
	_mergeSort(array, temp_array, 0, size - 1);
	free(temp_array);
}

int _partition(int* array, int size, int left, int right, int PI) {
	int return_pivot = left;
	int temp;

	temp = array[PI];
	array[PI] = array[right];
	array[right] = temp;

	for (int i = left; i < right; i++) {
		if (array[i] <= array[right]) {
			temp = array[i];
			array[i] = array[return_pivot];
			array[return_pivot] = temp;
			return_pivot++;
		}
	}

	temp = array[return_pivot];
	array[return_pivot] = array[right];
	array[right] = temp;

	return return_pivot;
}
void _quickSort(int* array, int size, int left, int right) {
	int pi, newPI;
	if (left >= right) {
		return;
	}
	else {
		pi = (left + right) / 2;
	}

	newPI = _partition(array, size, left, right, pi);

	if (left < (newPI - 1)) {
		_quickSort(array, size, left, newPI - 1);
	}

	if ((newPI - 1) < right) {
		_quickSort(array, size, newPI + 1, right);
	}
}
void quickSort(int* array, int size) {
	_quickSort(array, size, 0, size - 1);
}
