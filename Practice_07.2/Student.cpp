/*
Student.cpp
Date : 2026-04-16
Author : Lee Jong Kwang
Class function to load student information stored in a text file
*/

#include "Student.h"

/* 생성자, 클래스 변수 초기화 */
Student::Student() {
	name = "";
	addr = "";
	StID = 0;
	major = "";
	GPA = 0.0;
}

/* 클래스 변수 값 넣기 */
Student::Student(string name, string addr, int StID, string major, double GPA) {
	this->name = name;
	this->addr = addr;
	this->StID = StID;
	this->major = major;
	this->GPA = GPA;
}

/* 다른 학생 클래스와의 비교 */
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
		if (StID > other.StID) result = 1;
		else if (StID < other.StID) result = -1;
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
	st.StID = StID;
	st.major = major;
	st.GPA = GPA;

	return fin;
}

/* 클래스 출력을 위한 오버로딩 */
ostream& operator<<(ostream& fout, Student& st) {

	fout << "Student("
		<< right << setw(10) << st.name << ", "
		<< right << setw(10) << st.addr << ", "
		<< right << setw(5) << st.StID << ", "
		<< right << setw(10) << st.major << ", "
		<< right << setw(5) << st.GPA
		<< ")";

	return fout;
}