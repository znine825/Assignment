/*
Homework_07.4
Date : 2026-04-16
Author : Lee Jong Kwang
A function that loads student data stored in text as class data and sorts it according to specified criteria.
*/

#include "StudentDB.h"

using namespace std;

/* 메인 함수 기능 */
void main() {
	string input_data_file = "student_DB.txt";
	string Result_file = "Result.txt";
	ifstream fin;
	ofstream fout;
	StudentDB stDB;

	/* 파일이 똑바로 열리는지 확인 */
	fin.open(input_data_file);
	if (fin.fail()) {
		cout << "Fail to open input data file (" << input_data_file << ") !!!!" << endl;
		exit(1);
	}
	fout.open(Result_file);
	if (fout.fail()) {
		cout << "Fail to open output data file (" << Result_file << ") !!!!" << endl;
		exit(1);
	}


	cout << "File input from " << input_data_file << " . . . . " << endl;
	fin >> stDB; /* 클래스 데이터 입력 */
	cout << endl << "Initial state of StudentDB : " << endl;
	cout << stDB;
	/* 학생의 이름을 오름차순 정렬 */
	cout << endl << "Sorted StudentDB (keyAttr = NAME, sort_order = INCR) : " << endl;
	stDB.sortStudents(NAME, INCR);
	cout << stDB;
	/* 학생의 성적을 내림차순 정렬 */
	cout << endl << "Sorted StudentDB (keyAttr = GPA, sort_order = DECR) : " << endl;
	stDB.sortStudents(STGPA, DECR);
	cout << stDB;
	/* 학생의 학번을 오름차순 정렬 */
	cout << endl << "Sorted StudentDB (keyAttr = STID, sort_order = INCR) : " << endl;
	stDB.sortStudents(STID, INCR);
	cout << stDB;

	/* 위와 같은 내용을 파일로 출력 */
	fout << "File output from " << Result_file << " . . . . " << endl;
	fout << endl << "Initial state of StudentDB : " << endl;
	fout << stDB;

	fout << endl << "Sorted StudentDB (keyAttr = NAME, sort_order = INCR) : " << endl;
	stDB.sortStudents(NAME, INCR);
	fout << stDB;

	fout << endl << "Sorted StudentDB (keyAttr = GPA, sort_order = DECR) : " << endl;
	stDB.sortStudents(STGPA, DECR);
	fout << stDB;

	fout << endl << "Sorted StudentDB (keyAttr = STID, sort_order = INCR) : " << endl;
	stDB.sortStudents(STID, INCR);
	fout << stDB;

	fout.close();
	fin.close();
}