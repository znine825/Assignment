/*
Homework_07.3.cpp
Date : 2026-04-16
Author : Lee Jong Kwang
Matrix calculation program using matrix operator overloading
*/

#include "Mtrx.h"
#include "MtrxArray.h"

using namespace std;
#define NUM_MTRX 8

/* 메인 함수 기능 */
int main() {
	ifstream fin;
	ofstream fout;
	int n_row, n_col;

	/* 파일이 똑바로 읽어지는지 확인 */
	fin.open("Matrix_ABC.txt");
	if (fin.fail()) {
		cout << "Error in opening input data file !!" << endl;
		exit;
	}
	fout.open("Result.txt");
	if (fout.fail()) {
		cout << "Error in opening output data file !!" << endl;
		exit;
	}

	MtrxArray mtrx(NUM_MTRX);
	fin >> mtrx[0] >> mtrx[1] >> mtrx[2];
	mtrx[0].set_name("mtrx[0] =");
	mtrx[1].set_name("mtrx[1] =");
	mtrx[2].set_name("mtrx[2] =");

	/* 텍스트 파일에 저장된 행렬 정보 읽기 */
	fout << mtrx[0] << endl;
	fout << mtrx[1] << endl;
	fout << mtrx[2] << endl;

	/* 행렬 덧셈 */
	mtrx[3] = mtrx[0] + mtrx[1];
	mtrx[3].set_name("mtrx[3] = mtrx[0] + mtrx[1] =");
	fout << mtrx[3] << endl;
	/* 행렬 뺄셈 */
	mtrx[4] = mtrx[0] - mtrx[1];
	mtrx[4].set_name("mtrx[4] = mtrx[0] - mtrx[1] =");
	fout << mtrx[4] << endl;
	/* 행렬 곱셈 */
	mtrx[5] = mtrx[0] * mtrx[2];
	mtrx[5].set_name("mtrx[5] = mtrx[0] * mtrx[2] =");
	fout << mtrx[5] << endl;
	/* 행렬 transpose */
	mtrx[6] = ~mtrx[5]; // transpose
	mtrx[6].set_name("mtrx[6] = ~mtrx[5] (transposed matrix) =");
	fout << mtrx[6] << endl;

	/* 행렬 대입 */
	mtrx[7] = mtrx[0];
	mtrx[7].set_name("mtrx[7] = mtrx[0] =");
	fout << mtrx[7] << endl;

	/* 행렬 비교 */
	if (mtrx[0] == mtrx[7])
		fout << "mtrx[0] and mtrx[7] are equal.\n";
	if (mtrx[0] != mtrx[1])
		fout << "mtrx[0] and mtrx[1] are not equal.\n";

	fin.close();
	fout.close();
	return 0;
}