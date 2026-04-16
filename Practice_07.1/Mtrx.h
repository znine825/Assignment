/*
Mtrx.h
Date : 2026-04-16
Author : Lee Jong Kwang
Header file for creating mtrx class and implementing features for matrix operator overloading
*/

#define MAX_SIZE 100
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "MtrxArray.h"

using namespace std;
class MtrxArray;

class Mtrx {
	/* 파일 출력을 위한 연산자 오버로딩 기능 */
	friend ostream& operator<< (ostream&, const Mtrx&);
	/* 파일 읽기를 위한 연산자 오버로딩 기능*/
	friend istream& operator>> (istream&, Mtrx&);
	friend class MtrxArray;

public:
	/* mtrx 클래스 생성자, 변수 초기화 */
	Mtrx();
	/* mtrx 클래스에 대한 변수 내용 담기 기능*/
	Mtrx(string name, double* pA, int num_row, int num_col);
	/* mtrx 클래스 소멸자 */
	~Mtrx();

	void set_name(string name) { this->name = name; }
	string get_name() const { return name; }

	/* 행렬 연산자 오버로딩 + */
	const Mtrx operator+(const Mtrx&);
	/* 행렬 연산자 오버로딩 - */
	const Mtrx operator-(const Mtrx&);
	/* 행렬 연산자 오버로딩 * */
	const Mtrx operator*(const Mtrx&);
	/* 행렬 연산자 오버로딩 transpose */
	const Mtrx operator~();
	/* 행렬 연산자 오버로딩 = */
	const Mtrx& operator=(const Mtrx&);
	/* 행렬 연산자 오버로딩 == */
	bool operator==(const Mtrx&);
	/* 행렬 연산자 오버로딩 != */
	bool operator!=(const Mtrx&);
private:
	string name;
	int n_row;
	int n_col;
	double** dM;
};