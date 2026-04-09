/*
* 22312004 이종광
* Matrix.cpp
* 2026-04-02
* 행렬 정보가 담긴 파일 읽기
* 행렬 연산에 필요한 함수 구현
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix.h"


// 행렬 정보가 담긴 텍스트 파일을 읽어 구조체에 저장하는 함수
Mtrx* fgetMtrx(FILE* fin) {
	double data = 0.0;
	Mtrx* pM;

	if (fin == NULL) {
		printf("Error in get DoubleMartixData() - file pointer in NULL\n");
		return NULL;
	}

	// 행렬 기본 정렬 저장
	pM = (Mtrx*)calloc(1, sizeof(Mtrx));
	fscanf(fin, "%s %d %d", pM->name, &pM->n_row, &pM->n_col);
	pM->ppM = (double**)calloc(pM->n_row, sizeof(double*));

	// 2차원 배열이기 때문에 2중 for문으로 2중 동적 할당하며 데이터 저장
	for (int i = 0; i < pM->n_row; i++) {
		pM->ppM[i] = (double*)calloc(pM->n_col, sizeof(double));
		for (int j = 0; j < pM->n_col; j++) {
			fscanf(fin, "%lf", &data);
			pM->ppM[i][j] = data;
		}
	}
	return pM;
}

// 할당된 메모리 해제
void deleteMtrx(Mtrx* pM) {
	for (int i = 0; i < pM->n_row; i++) {
		free(pM->ppM[i]);
	}
	free(pM->ppM);
	free(pM);
}

// 행렬 정보 출력
void printMtrx(Mtrx* pM) {
	// 이름과 정보 출력
	printf("%s = (%d X %d)\n", pM->name, pM->n_row, pM->n_col);
	// 행렬 데이터 출력
	for (int i = 0; i < pM->n_row; i++) {
		for (int j = 0; j < pM->n_col; j++) {
			printf("%8.2f ", pM->ppM[i][j]);
		}
		printf("\n");
	}
}

// 행렬 덧셈
Mtrx* addMtrx(Mtrx* pM1, Mtrx* pM2) {
	Mtrx* paddM; // 새로운 구조체 변수 선언
	paddM = (Mtrx*)calloc(1, sizeof(Mtrx));
	paddM->n_row = pM1->n_row;
	paddM->n_col = pM1->n_col;

	// 2중 동적 할당 및 덧셈 연산
	paddM->ppM = (double**)calloc(paddM->n_row, sizeof(double*));
	for (int i = 0; i < paddM->n_row; i++) {
		paddM->ppM[i] = (double*)calloc(paddM->n_col, sizeof(double));
		for (int j = 0; j < paddM->n_col; j++) {
			paddM->ppM[i][j] = pM1->ppM[i][j] + pM2->ppM[i][j];
		}
	}

	return paddM;
}

// 행렬 뺄셈
Mtrx* subMtrx(Mtrx* pM1, Mtrx* pM2) {
	Mtrx* psubM; // 새로운 구조체 변수 선언
	psubM = (Mtrx*)calloc(1, sizeof(Mtrx));
	psubM->n_row = pM1->n_row;
	psubM->n_col = pM1->n_col;

	// 2중 동적 할당 및 뺄셈 연산
	psubM->ppM = (double**)calloc(psubM->n_row, sizeof(double*));
	for (int i = 0; i < psubM->n_row; i++) {
		psubM->ppM[i] = (double*)calloc(psubM->n_col, sizeof(double));
		for (int j = 0; j < psubM->n_col; j++) {
			psubM->ppM[i][j] = pM1->ppM[i][j] - pM2->ppM[i][j];
		}
	}
	return psubM;
}

// 행렬 곱셈
Mtrx* mulMtrx(Mtrx* pM1, Mtrx* pM2) {
	Mtrx* pmulM; // 새로운 구조체 변수 선언
	pmulM = (Mtrx*)calloc(1, sizeof(Mtrx));
	pmulM->n_row = pM1->n_row;
	pmulM->n_col = pM2->n_col;
	
	// 2중 동적 할당 및 곱셈 연산
	pmulM->ppM = (double**)calloc(pmulM->n_row, sizeof(double*));
	for (int i = 0; i < pmulM->n_row; i++) {
		pmulM->ppM[i] = (double*)calloc(pmulM->n_col, sizeof(double));
		for (int j = 0; j < pmulM->n_col; j++) {
			for (int k = 0; k < pM1->n_col; k++) {
				pmulM->ppM[i][j] += pM1->ppM[i][k] * pM2->ppM[k][j];
			}
		}
	}
	return pmulM;
}
// 전치행렬 구하기
Mtrx* transposeMtrx(Mtrx* pM) {
	Mtrx* pinvM; // 새로운 구조체 변수 선언
	pinvM = (Mtrx*)calloc(1, sizeof(Mtrx));
	pinvM->n_row = pM->n_col;
	pinvM->n_col = pM->n_row;


	pinvM->ppM = (double**)calloc(pinvM->n_row, sizeof(double*));
	for (int i = 0; i < pinvM->n_row; i++) {
		pinvM->ppM[i] = (double*)calloc(pinvM->n_col, sizeof(double));
		for (int j = 0; j < pinvM->n_col; j++) {

			// 인덱스 바꾸기
			pinvM->ppM[i][j] = pM->ppM[j][i];
		}
	}
	return pinvM;
}
