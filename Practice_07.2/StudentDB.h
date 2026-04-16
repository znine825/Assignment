/*
StudentDB.h
Date : 2026-04-16
Author : Lee Jong Kwang
Header file for implementing the DB function that stores student class data
*/

#ifndef CLASS_STUDENT_DB_H
#define CLASS_STUDENT_DB_H
#include "Student.h"

using namespace std;
class StudentDB {
	/* 클래스 입력을 위한 오버로딩 */
	friend istream& operator>>(istream&, StudentDB&);
	/* 클래스 출력을 위한 오버로딩 */
	friend ostream& operator<<(ostream&, StudentDB&);

public:
	/* 생성자, 클래스 변수 초기화 */
	StudentDB();
	/* 클래스 변수 값 넣기 */
	StudentDB(string db_name, int num_entries);
	/* 소멸자 */
	~StudentDB();
	/* 클래스 student 정렬 기능 */
	void sortStudents(ST_ATTR attr, SORT_ORDER sort_order);

private:
	string db_name;
	int num_entries;
	Student* students;
};
#endif
