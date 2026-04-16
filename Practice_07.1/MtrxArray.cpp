/*
MtrxArray.cpp
Date : 2026-04-16
Author : Lee Jong Kwang
Features for implementing an mtrx class array
*/

#include "Mtrx.h"

/* 생성자, 행렬 배열의 사이즈 정의 */
MtrxArray::MtrxArray(int size) {
	mtrxArrySize = size;
	this->pMtrx = new Mtrx[size];
	for (int i = 0; i < size; i++) {
		this->pMtrx[i] = Mtrx();
	}
}

/* 행렬 배열의 연산자 오버로딩 [], 인덱스가 정확한지 확인 기능*/
Mtrx& MtrxArray::operator[](int index) {
	if (!isValidIndex(index)) {
		cout << "ERROR: Subscript out of range.\n";
	}
	return this->pMtrx[index];
}

/* 인덱스가 정확한지 확인 기능 */
bool MtrxArray::isValidIndex(int indx) {
	if (indx < 0 || indx >= mtrxArrySize)
		return false;
	else
		return true;
}