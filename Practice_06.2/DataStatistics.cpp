#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "DataStatistics.h"


DataStatistics::DataStatistics(int max_size) {
	size = max_size;
	array = (int*)calloc(size, sizeof(size));
	num_element = 0;

	data_Statistics.min = 0;
	data_Statistics.max = 0;
	data_Statistics.avg = 0;
	data_Statistics.var = 0;
	data_Statistics.std_dev = 0;
}

DataStatistics::~DataStatistics() {
	free(array);
}

void DataStatistics::fgetData(istream& fin) {
	int n = 0;
	while (!fin.eof()) {
		fin >> array[n];
		n++;
	}
	num_element = n;
}

void DataStatistics::calcStatistics() {
	double s = 0;
	int a = 0;
	int m = array[0], l = array[0];

	for (int i = 0; i < num_element; i++) {
		if (array[i] < l) {
			l = array[i];
		}
		if (array[i] > m) {
			m = array[i];
		}
		s += array[i];
	}
	data_Statistics.min = l;
	data_Statistics.max = m;
	data_Statistics.avg = s / num_element;

	double temp = 0;
	for (int i = 0; i < num_element; i++) {
		temp += (array[i] - data_Statistics.avg) * (array[i] - data_Statistics.avg);
	}
	data_Statistics.var = temp / num_element;
	data_Statistics.std_dev = sqrt(data_Statistics.var);
}

void DataStatistics::printStatistics() {
	cout << fixed << setprecision(2);
	cout << "Statistics : " << endl;
	cout << "      num_element (" << num_element << "), min (" << data_Statistics.min << "), max (" << data_Statistics.max << "), avg (" << data_Statistics.avg << "), var (" << data_Statistics.var << "), std (" << data_Statistics.std_dev << ")";
	cout << endl;
}

void DataStatistics::printArraySample(int per_line, int num_sample_lines) {
	for (int i = 0; i < num_sample_lines; i++) {
		for (int j = 0; j < per_line; j++) {
			cout << setw(7) << array[i * num_sample_lines + j];
		}
		cout << endl;
	}
}

void DataStatistics::fprintStatistics(ostream& fout) {
	fout << fixed << setprecision(2);
	fout << "Statistics : " << endl;
	fout << "      num_element (" << num_element << "), min (" << data_Statistics.min << "), max (" << data_Statistics.max << "), avg (" << data_Statistics.avg << "), var (" << data_Statistics.var << "), std (" << data_Statistics.std_dev << ")";
	fout << endl;
}

void DataStatistics::fprintArraySample(ostream& fout, int per_line, int num_sample_lines) {
	fout.setf(ios::right);
	for (int i = 0; i < num_sample_lines; i++) {
		for (int j = 0; j < per_line; j++) {
			fout << setw(7) << array[i * num_sample_lines + j];
		}
		fout << endl;
	}
}