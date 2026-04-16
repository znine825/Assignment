/*
Student.h
Date : 2026-04-16
Author : Lee Jong Kwang
Header file for implementing the class function to load student information stored in a text file
*/

#ifndef CLASS_STUDENT_H
#define CLASS_STUDENT_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

enum ST_ATTR { NAME, ADDR, STID, MAJOR, STGPA };
enum SORT_ORDER { INCR, DECR };

class Student {
	/* 클래스 입력을 위한 오버로딩 */
	friend istream& operator>>(istream&, Student&);
	/* 클래스 출력을 위한 오버로딩 */
	friend ostream& operator<<(ostream&, Student&);

public:
	/* 생성자, 클래스 변수 초기화 */
	Student();
	/* 클래스 변수 값 넣기 */
	Student(string name, string addr, int StID, string major, double GPA);

	void setName(string nm) { this->name = nm; }
	void setAddr(string addr) { this->addr = addr; }
	void setStID(int st_id) { this->StID = st_id; }
	void setMajor(string major) { this->major = major; }
	void setGPA(double gpa) { this->GPA = gpa; }
	string getName() { return this->name; }
	string getAddr() { return this->addr; }
	int getStID() { return this->StID; }
	string getMajor() { return this->major; }
	double getGPA() { return this->GPA; }

	/* 다른 학생 클래스와의 비교 */
	int compareStudent(Student& other, ST_ATTR stAttr, SORT_ORDER order);
private:
	string name;
	string addr;
	int StID;
	string major;
	double GPA;
};
#endif