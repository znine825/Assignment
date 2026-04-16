/*
StudentDB.cpp
Date : 2026-04-16
Author : Lee Jong Kwang
DB function that stores student class data
*/

#include "StudentDB.h"
#include "Student.h"

/* 생성자, 클래스 변수 초기화 */
StudentDB::StudentDB() {
	db_name = "";
	num_entries = 0;
	students = nullptr;
}

/* 클래스 변수 값 넣기 */
StudentDB::StudentDB(string db_name, int num_entries) {
	this->db_name = db_name;
	this->num_entries = num_entries;
	students = new Student[num_entries];
}

/* 소멸자 */
StudentDB::~StudentDB() {
	delete[] students;
}

/* 클래스 student 정렬 기능, 삽입 정렬 */
void StudentDB::sortStudents(ST_ATTR attr, SORT_ORDER sort_order) {
	for (int i = 1; i < num_entries; i++) {
		Student key = students[i];
		int j = i - 1;

		/* compareStudent 를 이용하여 값 비교 */
		while (j >= 0 && students[j].compareStudent(key, attr, sort_order) > 0) {
			students[j + 1] = students[j];
			j--;
		}
		students[j + 1] = key;
	}
}

/* 클래스 입력을 위한 오버로딩 */
istream& operator>>(istream& fin, StudentDB& st) {
	string DBname;
	int st_num;

	fin >> DBname >> st_num;
	st.num_entries = st_num;
	st.db_name = DBname;

	st.students = new Student[st_num];

	for (int i = 0; i < st.num_entries; i++) {
		fin >> st.students[i];
	}
	return fin;
}

/* 클래스 출력을 위한 오버로딩 */
ostream& operator<<(ostream& fout, StudentDB& st) {
	fout << "StudentDB (" << st.db_name << ", num_students = " << st.num_entries << ")" << endl;
	for (int i = 0; i < st.num_entries; i++) {
		fout << st.students[i] << endl;
	}
	return fout;
}