/*
22312004 이종광
Student.cpp
2026-04-02
학생정보 출력과 학생 데이터베이스 출력
학생 데이터베이스 정렬기능
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Student.h"

// 학생 데이터베이스를 파일에서 읽어오는 함수
StudentDB* fgetStudentDB(FILE* fin) {
	StudentDB* db;

	if (fin == NULL) { // 파일을 읽어오지 못한 경우
		printf("Error in get StudentData() - file pointer in NULL\n");
		return NULL;
	}

	// 학생 데이터베이스 구조체 동적 메모리 할당
	db = (StudentDB*)calloc(1, sizeof(StudentDB));
	fscanf(fin, "%s %d", db->name, &db->num_students);
	db->students = (Student*)calloc(db->num_students, sizeof(Student));
	for (int i = 0; i < db->num_students; i++) {
		fscanf(fin, "%d %s %s %lf", &db->students[i].id, db->students[i].name, db->students[i].major, &db->students[i].GPA);
	}

	return db;
}

// 할당된 메모리 해제
void delete_StudentDB(StudentDB* db) {
	free(db->students);
	free(db);
}

// 학생 정보 출력 함수
void print_Student(Student* db) {
	printf("Student [st_ID: %8d, st_NAME: %10s, Major: %10s, GPA: %7.2f]\n",
		db->id, db->name, db->major, db->GPA);
}
// 학생 데이터베이스 출력 함수
void print_StudentDB(StudentDB* db) {
	printf("StudentDB :\n");
	for (int i = 0; i < db->num_students; i++) {
		print_Student(&db->students[i]);
	}
}


// 학생을 standard과 mode에 따라 비교하는 함수
int compare_Student(Student* a, Student* b, ST_STANDARD standard, SORT_MODE mode) {
	int result = 0;
	switch (standard)
	{
	case ID:
		if (a->id > b->id) result = 1;
		else if (a->id < b->id)  result = -1;
		else result = 0;
		break;
	case NAME:
		result = strcmp(a->name, b->name);
		break;
	case MAJOR:
		result = strcmp(a->major, b->major);
		break;
	case GPA:
		if (a->GPA > b->GPA) result = 1;
		else if (a->GPA < b->GPA)  result = -1;
		else result = 0;
		break;
	}
	if (mode == DE) result *= -1;
	return result;
}

// 학생 데이터베이스를 standard과 mode에 따라 정렬하는 함수 (삽입 정렬)
void sorting_StudentDB(StudentDB* db, ST_STANDARD standard, SORT_MODE mode) {
	int size = db->num_students;
	for (int i = 1; i < size; i++) {
		Student key = db->students[i];
		int j = i - 1;

		// compare_Student 를 이용하여 정렬
		while (j >= 0 && compare_Student(&db->students[j], &key, standard, mode) > 0) {
			db->students[j + 1] = db->students[j];
			j--;
		}
		db->students[j + 1] = key;
	}
}