#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

using namespace std;

struct Statistics {
	int min;
	int max;
	double avg;
	double var;
	double std_dev;
};

class DataStatistics {
public:
	DataStatistics(int max_size);
	~DataStatistics();

	void fgetData(istream& fin);
	void calcStatistics();
	void printStatistics();
	void printArraySample(int per_line, int num_sample_lines);

	void fprintStatistics(ostream& fout);
	void fprintArraySample(ostream& fout, int per_line, int num_sample_lines);

private:
	int* array;
	int size;
	int num_element;
	Statistics data_Statistics;
};