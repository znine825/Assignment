/*
Person.cpp
Date : 2026-05-08
Author : Lee Jong Kwang
- Basic settings for the Person class
*/

#include "Person.h"

/* 기본 생성자 */
Person::Person() {
	name = "";
	addr = "";
}

/* 매개변수 생성자 */
Person::Person(const string name, const string addr) {
	this->name = name;
	this->addr = addr;
}
/* 소멸자 */
Person::~Person() {
	/* 쉬었음 청년 */
}

/* 클래스 입력을 위한 오버로딩 */
istream& operator>>(istream& fin, Person&) {
	/* 사용하지 않음 */
	return fin;
}

/* 클래스 출력을 위한 오버로딩 */
ostream& operator<<(ostream& fout, const Person&) {
	/* 사용하지 않음*/
	return fout;
}