/*
Practice_08.1.cpp
Date : 2026-05-08
Author : Lee Jong Kwang
- Read and save student information included in class StudentDB from a file
- Sort students in descending order of specified attributes, and output the sorted results to the console and file
*/

#include <fstream>
#include "StudentDB.h"

/* 메인 함수 */
void main() {
	string input_data_file = "student_DB.txt";
	ifstream fin;
	StudentDB stDB;
	fin.open(input_data_file);

	/* 파일 잘 열리는지 확인 */
	if (fin.fail()) {
		cout << "Fail to open input data file (" << input_data_file << ") !!!!" << endl;
		exit(1);
	}

	cout << "File input from " << input_data_file << " . . . . " << endl;
	fin >> stDB;
	fin.close();
	cout << endl << "Initial state of StudentDB : " << endl;
	cout << stDB;

	/* NAME 기준으로 오름차순 정렬 */
	cout << endl << "Sorted StudentDB (keyAttr = NAME, sort_order = INCR) : " << endl;
	stDB.sortStudents(NAME, INCR);
	cout << stDB;

	/* GPA 기준으로 내림차순 정렬 */
	cout << endl << "Sorted StudentDB (keyAttr = GPA, sort_order = DECR) : " << endl;
	stDB.sortStudents(STGPA, DECR);
	cout << stDB;

	/* STID 기준으로 오름차순 정렬 */
	cout << endl << "Sorted StudentDB (keyAttr = STID, sort_order = INCR) : " << endl;
	stDB.sortStudents(STID, INCR);
	cout << stDB;
}