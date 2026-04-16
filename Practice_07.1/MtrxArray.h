/*
MtrxArray.h
Date : 2026-04-16
Author : Lee Jong Kwang
Header file for implementing mtrx class array functionality
*/

#ifndef MTRX_ARRAY_H
#define MTRX_ARRAY_H

using namespace std;
class Mtrx;
class MtrxArray
{
public:
	/* 생성자, 행렬 배열의 사이즈 정의 */
	MtrxArray(int array_size);
	/* 행렬 배열의 연산자 오버로딩 [], 인덱스가 정확한지 확인 기능*/
	Mtrx& operator[](int);
private:
	Mtrx* pMtrx;
	int mtrxArrySize;
	/* 인덱스가 정확한지 확인 기능 */
	bool isValidIndex(int index);
};
#endif