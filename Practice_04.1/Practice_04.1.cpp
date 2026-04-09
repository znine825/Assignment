#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "BigArray.h"

int main(void) {
	int* testArray;
	
	int sTestSize[] = { 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140, 145, 150 };
	int bTestSize[] = { 100, 1000, 10000, 100000, 500000, 1000000, 5000000, 10000000, 50000000, 100000000 };
	int sTestSize_n = sizeof(sTestSize) / sizeof(int);
	int bTestSize_n = sizeof(bTestSize) / sizeof(int);

	LARGE_INTEGER freq, t1, t2;
	LONGLONG tDiff;
	double elapsedTimeMs;

	QueryPerformanceFrequency(&freq);
	printf("1. Compare the performeances of sorting algorithms for small array\n");
	printf("==================================================================================\n");
	printf(" Array size    QuickSort[ms]    MergeSort[ms]  InsertionSort[ms] SelectionSort[ms]\n");
	printf("----------------------------------------------------------------------------------\n");

	for (int i = 0; i < sTestSize_n; i++) {
		int size = sTestSize[i];

		printf("%11d", size);

		testArray = genBigRandArray(size, 0);
		QueryPerformanceCounter(&t1);
		quickSort(testArray, size);
		QueryPerformanceCounter(&t2);
		tDiff = t2.QuadPart - t1.QuadPart;
		elapsedTimeMs = ((double)tDiff * 1000 / freq.QuadPart);
		printf("%17.2lf", elapsedTimeMs);

		shuffleBigArray(testArray, size);
		QueryPerformanceCounter(&t1);
		mergeSort(testArray, size);
		QueryPerformanceCounter(&t2);
		tDiff = t2.QuadPart - t1.QuadPart;
		elapsedTimeMs = ((double)tDiff * 1000 / freq.QuadPart);
		printf("%17.2lf", elapsedTimeMs);

		shuffleBigArray(testArray, size);
		QueryPerformanceCounter(&t1);
		insertSort(testArray, size);
		QueryPerformanceCounter(&t2);
		tDiff = t2.QuadPart - t1.QuadPart;
		elapsedTimeMs = ((double)tDiff * 1000 / freq.QuadPart);
		printf("%19.2lf", elapsedTimeMs);

		shuffleBigArray(testArray, size);
		QueryPerformanceCounter(&t1);
		selectSort(testArray, size);
		QueryPerformanceCounter(&t2);
		tDiff = t2.QuadPart - t1.QuadPart;
		elapsedTimeMs = ((double)tDiff * 1000 / freq.QuadPart);
		printf("%18.2lf\n", elapsedTimeMs);

	}

	QueryPerformanceFrequency(&freq);
	printf("\n\n2. Compare the performeances of sorting algorithms for big array\n");
	printf("==================================================================================\n");
	printf(" Array size    QuickSort[ms]    MergeSort[ms]  InsertionSort[ms] SelectionSort[ms]\n");
	printf("----------------------------------------------------------------------------------\n");

	for (int i = 0; i < bTestSize_n; i++) {
		int size = bTestSize[i];

		printf("%11d", size);

		testArray = genBigRandArray(size, 0);
		QueryPerformanceCounter(&t1);
		quickSort(testArray, size);
		QueryPerformanceCounter(&t2);
		tDiff = t2.QuadPart - t1.QuadPart;
		elapsedTimeMs = ((double)tDiff * 1000 / freq.QuadPart);
		printf("%17.2lf", elapsedTimeMs);

		shuffleBigArray(testArray, size);
		QueryPerformanceCounter(&t1);
		mergeSort(testArray, size);
		QueryPerformanceCounter(&t2);
		tDiff = t2.QuadPart - t1.QuadPart;
		elapsedTimeMs = ((double)tDiff * 1000 / freq.QuadPart);
		printf("%17.2lf", elapsedTimeMs);

		if (size < 50000) {
			shuffleBigArray(testArray, size);
			QueryPerformanceCounter(&t1);
			insertSort(testArray, size);
			QueryPerformanceCounter(&t2);
			tDiff = t2.QuadPart - t1.QuadPart;
			elapsedTimeMs = ((double)tDiff * 1000 / freq.QuadPart);
			printf("%19.2lf", elapsedTimeMs);

			shuffleBigArray(testArray, size);
			QueryPerformanceCounter(&t1);
			selectSort(testArray, size);
			QueryPerformanceCounter(&t2);
			tDiff = t2.QuadPart - t1.QuadPart;
			elapsedTimeMs = ((double)tDiff * 1000 / freq.QuadPart);
			printf("%18.2lf\n", elapsedTimeMs);
		}
		else {
			printf("                  -                 -\n");
		}


	}

	return 0;
}