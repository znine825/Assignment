/*
Person.h
Date : 2026-05-08
Author : Lee Jong Kwang
- Class file for implementing Person class functionality
*/

#ifndef CLASS_PERSON_H
#define CLASS_PERSON_H
#include <string>

using namespace std;

class Person {
	/* 클래스 입력을 위한 오버로딩 */
	friend istream& operator>>(istream&, Person&);
	/* 클래스 출력을 위한 오버로딩 */
	friend ostream& operator<<(ostream&, const Person&);

public:
	/* 기본 생성자 */
	Person();
	/* 매개변수 생성자 */
	Person(const string name, const string addr);
	/* 소멸자 */
	~Person();

protected:
	string name;
	string addr;
};
#endif