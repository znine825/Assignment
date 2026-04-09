/*
* 22312004 이종광
* Matrix.h
* 2026-04-02
* 행렬 구조체 및 연산에 관한 해더 파일
*/

typedef struct {
	char name[64];
	int n_row;
	int n_col;
	double** ppM;
} Mtrx; // 구조체 선연

// 행렬 정보가 담긴 텍스트 파일을 읽어 구조체에 저장하는 함수
Mtrx* fgetMtrx(FILE* fin);

// 행렬 정보 출력
void printMtrx(Mtrx* pM);

// 행렬 구조체에 할당된 메모리 해제
void deleteMtrx(Mtrx* pM);

// 행렬 덧셈, 뺄셈, 곱셈
Mtrx* addMtrx(Mtrx* pM1, Mtrx* pM2);
Mtrx* subMtrx(Mtrx* pM1, Mtrx* pM2);
Mtrx* mulMtrx(Mtrx* pM1, Mtrx* pM2);
Mtrx* transposeMtrx(Mtrx* pM);