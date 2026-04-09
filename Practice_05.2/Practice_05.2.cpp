/*
22312004 이종광
Practice 05.2
2026-04-02
학생 정보가 담긴 텍스트 파일을 읽어오는 프로그램
학생 데이터베이스를 이용해 제시된 키에 따라서 학생들을 정렬하는 프로그램.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Student.h"
#define MAX_NUM_STUDENTS 100
void main()
{

	FILE* fin;
	const char* Student_file = "StudentRecords.txt";
	StudentDB* pST_DB;

	// 파일 오픈
	fin = fopen(Student_file, "r");
	if (fin == NULL) { // 실패시
		printf("Error in opening data file\n");
		exit;
	}

	pST_DB = fgetStudentDB(fin);
	fclose(fin); // 파일 닫기

	// 기본 학생 데이터베이스 출력
	printf("Initial status of Student DB:\n");
	print_StudentDB(pST_DB); printf("\n");

	// 학생 ID를 기준으로 오름차순 정렬
	sorting_StudentDB(pST_DB, ID, IN);
	printf("After sorting students by increasing order of student ID:\n");
	print_StudentDB(pST_DB); printf("\n");

	// 학생 전공을 기준으로 오름차순 정렬
	sorting_StudentDB(pST_DB, MAJOR, IN);
	printf("After sorting students by increasing order of major:\n");
	print_StudentDB(pST_DB); printf("\n");

	// 학생 GPA를 기준으로 내림차순 정렬
	sorting_StudentDB(pST_DB, GPA, DE);
	printf("After sorting students by decreasing order of GPA:\n");
	print_StudentDB(pST_DB); printf("\n");

	// 학생 이름을 기준으로 오름차순 정렬
	sorting_StudentDB(pST_DB, NAME, IN);
	printf("After sorting students by increasing order of student name:\n");
	print_StudentDB(pST_DB); printf("\n");

	// 할당된 메모리 해제
	delete_StudentDB(pST_DB);

}