/*
* 22312004 이종광
* Practice 05.1
* 2026-04-02
* 행렬 정보가 담긴 텍스트 파일을 읽기
* 읽은 행렬 파일을 구조체에 저장 후 행렬 연산 하기.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix.h"

// 메인 함수
int main(void) {

	FILE* fin_Mtrx;
	const char* input_file = "Mtrx_ABC.txt";

	Mtrx* mA, * mB, * mC, * mD, * mE, * mF, * mG;

	// 파일 오픈
	fin_Mtrx = fopen(input_file, "r");

	// 오픈 실패시
	if (fin_Mtrx == NULL) {
		printf("Error in opening input data file (input_file)");
		exit;
	}

	// 기본 저장된 행렬 정보 읽기 및 출력
	mA = fgetMtrx(fin_Mtrx);
	printMtrx(mA);
	mB = fgetMtrx(fin_Mtrx);
	printMtrx(mB);
	mC = fgetMtrx(fin_Mtrx);
	printMtrx(mC);
	fclose(fin_Mtrx);

	// 행렬 덧셈
	mD = addMtrx(mA, mB);
	strcpy(mD->name, "mD = (mA + mB)");
	printMtrx(mD);

	// 행렬 뺄셈
	mE = subMtrx(mA, mB);
	strcpy(mE->name, "mE = (mA - mB)");
	printMtrx(mE);

	// 행렬 곱셈
	mF = mulMtrx(mA, mC);
	strcpy(mF->name, "mF = (mA * mC)");
	printMtrx(mF);

	// 전치행렬
	mG = transposeMtrx(mA);
	strcpy(mG->name, "mG = transposeMtrx (mA)");
	printMtrx(mG);

	// 할당된 메모리 해제
	deleteMtrx(mA); deleteMtrx(mB); deleteMtrx(mC);
	deleteMtrx(mD); deleteMtrx(mE); deleteMtrx(mF);

	return 0;
}
