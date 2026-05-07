/*
Student.cpp
Date : 2026-05-08
Author : Lee Jong Kwang
- Function that inherits from class Person and includes student ID, major, and grade as additional attributes
- Function to compare student information
*/

#include "Student.h"

/* 기본 생성자 */
Student::Student()
	: Person() {
	stID = 0;
	major = "";
	GPA = 0;
}

/* 매개변수 생성자 */
Student::Student(string name, string addr, int stID, string major, double GPA)
	: Person(name, addr) {
	this->stID = stID;
	this->major = major;
	this->GPA = GPA;
}

/* 소멸자 */
Student::~Student() {
	/* 쉬었음 청년 */
}

/* 학생들 정보 비교 기능 */
int Student::compareStudent(Student& other, ST_ATTR stAttr, SORT_ORDER order) {
	int result = 0;
	switch (stAttr) {
	case NAME:
		if (name > other.name) result = 1;
		else if (name < other.name) result = -1;
		else result = 0;
		break;
	case ADDR:
		if (addr > other.addr) result = 1;
		else if (addr < other.addr) result = -1;
		else result = 0;
		break;
	case STID:
		if (stID > other.stID) result = 1;
		else if (stID < other.stID) result = -1;
		else result = 0;
		break;
	case MAJOR:
		if (major > other.major) result = 1;
		else if (major < other.major) result = -1;
		else result = 0;
		break;
	case STGPA:
		if (GPA > other.GPA) result = 1;
		else if (GPA < other.GPA) result = -1;
		else result = 0;
		break;
	default:
		break;
	}
	if (order == DECR) result *= -1;
	return result;
}

/* 클래스 입력을 위한 오버로딩 */
istream& operator>>(istream& fin, Student& st) {
	string name, major, addr;
	int StID;
	double GPA;

	fin >> name >> addr >> StID >> major >> GPA;
	st.name = name;
	st.addr = addr;
	st.stID = StID;
	st.major = major;
	st.GPA = GPA;

	return fin;
}

/* 클래스 출력을 위한 오버로딩 */
ostream& operator<<(ostream& fout, Student& st) {
	fout << "Student("
		<< right << setw(10) << st.name << ", "
		<< right << setw(10) << st.addr << ", "
		<< right << setw(5) << st.stID << ", "
		<< right << setw(10) << st.major << ", "
		<< right << setw(5) << st.GPA
		<< ")";

	return fout;
}