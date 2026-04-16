/*
Mtrx.cpp
Date : 2026-04-16
Author : Lee Jong Kwang
Creation of mtrx class for matrix operator overloading and implementation of features
*/

#include "Mtrx.h"
#include "MtrxArray.h"


/* mtrx 클래스 생성자, 변수 초기화 */
Mtrx::Mtrx() {
	name = "";
	n_row = 0;
	n_col = 0;
	dM = nullptr;
}
/* mtrx 클래스에 대한 변수 내용 담기 기능*/
Mtrx::Mtrx(string name, double* pA, int num_row, int num_col) {
	this->name = name;
	n_row = num_row;
	n_col = num_col;
	dM = new double* [n_row];
	for (int i = 0; i < n_row; i++) {
		dM[i] = new double[n_col];
		for (int j = 0; j < n_col; j++) {
			dM[i][j] = pA[i * n_col + j];
		}
	}
}
/* mtrx 클래스 소멸자 */
Mtrx::~Mtrx() {
	for (int i = 0; i < n_row; i++) {
		delete[] dM[i];
	}
	delete[] dM;
}
/* 파일 출력을 위한 연산자 오버로딩 기능 */
ostream& operator<<(ostream& fout, const Mtrx& m) {
	fout << m.name << endl;
	fout.setf(ios::fixed);
	fout.precision(2);
	for (int i = 0; i < m.n_row; i++) {
		for (int j = 0; j < m.n_col; j++) {
			fout << setw(9) << m.dM[i][j];
		}
		fout << endl;
	}
	return fout;
}
/* 파일 읽기를 위한 연산자 오버로딩 기능*/
istream& operator>> (istream& fin, Mtrx& m) {
	string name;
	int num_row, num_col;
	double d;
	/* 행렬 기본 정보 읽기*/
	fin >> num_row >> num_col;
	m.n_row = num_row;
	m.n_col = num_col;
	m.dM = new double* [num_row]();
	/* 행렬 원소값 읽기 */
	for (int r = 0; r < num_row; r++) {
		m.dM[r] = new double[num_col]();
		for (int c = 0; c < num_col; c++) {
			fin >> d;
			m.dM[r][c] = d;
		}
	} return fin;
}

/* 행렬 연산자 오버로딩 + */
const Mtrx Mtrx::operator+(const Mtrx& mA) {
	double* temp = new double[n_row * n_col];
	Mtrx mR("mR", temp, this->n_row, this->n_col);

	for (int i = 0; i < this->n_row; i++) {
		for (int j = 0; j < this->n_col; j++) {
			mR.dM[i][j] = this->dM[i][j] + mA.dM[i][j];
		}
	}
	return mR;
}
/* 행렬 연산자 오버로딩 - */
const Mtrx Mtrx::operator-(const Mtrx& mA) {
	double* temp = new double[n_row * n_col];
	Mtrx mR("mR", temp, this->n_row, this->n_col);
	for (int i = 0; i < this->n_row; i++) {
		for (int j = 0; j < this->n_col; j++) {
			mR.dM[i][j] = this->dM[i][j] - mA.dM[i][j];
		}
	}
	return mR;
}
/* 행렬 연산자 오버로딩 * */
const Mtrx Mtrx::operator*(const Mtrx& mA) {
	double* temp = new double[n_row * n_col];
	Mtrx mR("mR", temp, this->n_row, mA.n_col);
	for (int i = 0; i < this->n_row; i++) {
		for (int j = 0; j < mA.n_col; j++) {
			mR.dM[i][j] = 0;
			for (int k = 0; k < this->n_col; k++) {
				mR.dM[i][j] += this->dM[i][k] * mA.dM[k][j];
			}
		}
	}
	return mR;
}
/* 행렬 연산자 오버로딩 transpose */
const Mtrx Mtrx::operator~() {
	double* temp = new double[n_row * n_col];
	Mtrx mR("mR", temp, this->n_col, this->n_row);
	for (int i = 0; i < this->n_row; i++) {
		for (int j = 0; j < this->n_col; j++) {
			mR.dM[j][i] = this->dM[i][j]; /* 위치 전치*/
		}
	}
	return mR;
}
/* 행렬 연산자 오버로딩 = */
const Mtrx& Mtrx::operator=(const Mtrx& mA) {
	if (this != &mA) {
		for (int i = 0; i < n_row; i++) {
			delete[] dM[i];
		}
		delete[] dM;
		n_row = mA.n_row;
		n_col = mA.n_col;
		dM = new double* [n_row];
		for (int i = 0; i < n_row; i++) {
			dM[i] = new double[n_col];
			for (int j = 0; j < n_col; j++) {
				dM[i][j] = mA.dM[i][j]; /* 새로운 행렬 클래스에 대입 */
			}
		}
	}
	return *this;
}

/* 행렬 연산자 오버로딩 == */
bool Mtrx::operator==(const Mtrx& mA) {
	if (this->n_row != mA.n_row || this->n_col != mA.n_col) {
		return false;
	}
	for (int i = 0; i < this->n_row; i++) {
		for (int j = 0; j < this->n_col; j++) {
			if (this->dM[i][j] != mA.dM[i][j]) {
				return false; /* 하나라도 다르면 다른 행렬 */
			}
		}
	}
	return true;
}

/* 행렬 연산자 오버로딩 != */
bool Mtrx::operator!=(const Mtrx& mA) {
	return !(*this == mA); /* == 의 반대로 구현 */
}