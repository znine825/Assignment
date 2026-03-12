#include <stdio.h>
#include <limits.h>
#include <math.h>

#define NUM_DATA 10

int main(void) {

	int int_dataL[NUM_DATA];

	printf("input %d integer data : ", NUM_DATA);

	for (int i = 0; i < NUM_DATA; i++) {
		scanf("%d", &int_dataL[i]);
	}

	int min = INT_MAX;
	int max = INT_MIN;
	float avg;
	float sum = 0;


	for (int i = 0; i < NUM_DATA; i++) {
		sum = sum + int_dataL[i];
		if (min > int_dataL[i]) {
			min = int_dataL[i];
		}
		if (max < int_dataL[i]) {
			max = int_dataL[i];
		}
	}

	avg = sum / NUM_DATA;

	printf("data_max = %d, data_min = %d, data_avg = %lf\n", max, min, avg);
	return 0;
}