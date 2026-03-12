#include <stdio.h>

void draw_RightTriangle(int base) {
	for (int i = 0; i <= base / 2; i++) {
		if (i == 0) {
			for (int j = 0; j < base / 2; j++) {
				printf(" ");
			}
			printf("*");
			for (int j = 0; j < base / 2; j++) {
				printf(" ");
			}
		}
		else if (i == (base / 2)) {
			for (int j = 0; j < base; j++) {
				printf("*");
			}
		}
		else {
			for (int j = 0; j < base / 2 - i; j++) {
				printf(" ");
			}
			printf("*");
			for (int j = 0; j < i * 2 - 1; j++) {
				printf(" ");
			}
			printf("*");
		}
		printf("\n");
	}
}

int main(void) {

	int base;

	while (true) {
		printf("Enter base (odd number >= 3; 0 to quit): ");
		scanf("%d", &base);

		if (base == 0) break;
		if (base < 3 || (base % 2) == 0) {
			printf("Invalid input. Base must be an odd number >= 3.\n");
			continue;
		}

		draw_RightTriangle(base);
	}

	return 0;
}

