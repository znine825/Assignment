#include <stdio.h>
#define DATA_SIZE 20
#define PER_LINE 10

void inputArray(int* array, int size) {
    int temp;
    printf("Input %d integer data for  in a line : ", size);
    for (int i = 0; i < DATA_SIZE; i++) {
        scanf(" %d", &temp);
        array[i] = temp;
    }
}

void printArray(int* array, int size, int per_line) {
    for (int i = 0; i < size / per_line; i++) {
        for (int j = 0; j < per_line; j++) {
            printf("%5d", array[i * per_line + j]);
        }
        printf("\n");
    }
}

void insertSort(int* array, int size) {

    for (int i = 1; i < size; i++) {
        int key = array[i];
        for (int j = i; j > 0; j--) {
            if (key < array[j - 1]) {
                array[j] = array[j - 1];
                array[j - 1] = key;
            }
            else {
                break;
            }
        }

    }
}

int binarySearch(int* array, int size, int key_search) {

    int start = 0;
    int end = size - 1;
    int loop = 0;

    while (start <= end) {

        loop++;
        printf("%2d-th loop : Search range [%2d ~ %2d]\n", loop, start, end);

        int mid = (start + end) / 2;
        if (array[mid] == key_search) {
            return mid;
        }
        else if (array[mid] < key_search) {
            start = mid + 1;
        }
        else if (array[mid] > key_search) {
            end = mid - 1;
        }

    }
    return -1;
}

int main(void) {

    int array[DATA_SIZE];

    inputArray(array, DATA_SIZE);
    insertSort(array, DATA_SIZE);
    printArray(array, DATA_SIZE, PER_LINE);


    while (true) {

        int find_int;
        printf("Input integer to be search (-1 to quit) : ");
        scanf("%d", &find_int);

        if (find_int == -1) {
            break;
        }

        printf("Sequential searching key (%d) from array of %d data ...\n", find_int, DATA_SIZE);
        int pos = binarySearch(array, DATA_SIZE, find_int);
        if (pos == -1) {
            printf("The key (%2d) wos not found from the array\n\n", find_int);
        }
        else {
            printf("The key(%2d) was found at posotion (%2d)\n\n", find_int, pos);
        }
    }
    return 0;
}