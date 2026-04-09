#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 500
#include <iostream>
#include <fstream>
#include "DataStatistics.h"

using namespace std;


int main(void) {
	ifstream fin;
	ofstream fout;
	DataStatistics dataStat(MAX_SIZE);
	fin.open("data.txt");
	fout.open("data_statistics.txt");

	if (fin.fail()) {
		cout << "Fail to open data input file (data.text)" << endl;
		exit(1);
	}
	if (fout.fail()) {
		cout << "Fail to open data output file (data_statistics.text)" << endl;
		exit(1);
	}

	dataStat.fgetData(fin);
	cout << "input_data" << endl;
	dataStat.printArraySample(10, 2);
	dataStat.calcStatistics();
	dataStat.printStatistics();

	fout << "input_data" << endl;
	dataStat.fprintArraySample(fout, 10, 2);
	dataStat.fprintStatistics(fout);
}