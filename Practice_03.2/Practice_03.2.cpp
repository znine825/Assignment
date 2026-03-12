#include <stdio.h>
#include <Windows.h>
#define FIBO_TBL_SIZE 200

double Fibo_SR(int n) {
	if (n == 0) {
		return 0;
	}
	else if (n == 1) {
		return 1;
	}
	else {
		return Fibo_SR(n - 1) + Fibo_SR(n - 2);
	}
}

double Fibo_Dyn(int n) {

	static double Fibo_array[FIBO_TBL_SIZE] = { 0 };
	if (n == 0) {
		return 0;
	}
	else if (n == 1) {
		return 1;
	}
	else if (Fibo_array[n] != 0) {
		return Fibo_array[n];
	}
	else {
		double temp = Fibo_Dyn(n - 1) + Fibo_Dyn(n - 2);
		Fibo_array[n] = temp;
		return temp;
	}
}

int main(void) {

	double fibo_n_SR, t_elapse_ms, fibo_n_Dyn;
	LONGLONG t_diff_pc;
	LARGE_INTEGER freq, t1, t2;

	QueryPerformanceFrequency(&freq);

	printf("----------------------------------------------------------------------------------------\n");
	printf("%8s %23s %15s %23s %15s\n", "n", "FiboDyn()", "Elapse_Time[ms]", "FiboSR()", "Elapse_Time[ms]");
	printf("----------------------------------------------------------------------------------------\n");

	for (int i = 0; i <= 100; i++) {
		QueryPerformanceCounter(&t1);
		fibo_n_Dyn = Fibo_Dyn(i);
		QueryPerformanceCounter(&t2);

		t_diff_pc = t2.QuadPart - t1.QuadPart;
		t_elapse_ms = ((double)t_diff_pc / (double)freq.QuadPart) * 1000000;
		printf("%8d %23.0lf %15.3lf", i, fibo_n_Dyn, t_elapse_ms);

		if (i <= 44) {
			QueryPerformanceCounter(&t1);
			fibo_n_SR = Fibo_SR(i);
			QueryPerformanceCounter(&t2);

			t_diff_pc = t2.QuadPart - t1.QuadPart;
			t_elapse_ms = ((double)t_diff_pc / (double)freq.QuadPart) * 1000000;
			printf(" %23.0lf %15.3lf", fibo_n_SR, t_elapse_ms);
		}
		else {
			i += 4;
		}
		printf("\n");
	}
	printf("----------------------------------------------------------------------------------------\n");
}