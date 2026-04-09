#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Student.h"
#define MAX_NUM_STUDENTS 100
void main()
{
	StudentDB stDB;
	StudentDB* pST_DB = &stDB;
	Student students[] = {
	{21911000, "Kim_GM", "InfoEng", 3.57}, {21612075, "Zhang_SM", "MechEng", 4.37},
	{21431015, "Hwang_SS", "ChemEng", 2.72}, {21641054, "Lee_KM", "ElecEng", 3.35},
	{21851340, "Hong_GM", "Music", 3.57}, {21762056, "Jang_SM", "Art", 4.45},
	{21271017, "Park_SS", "Management", 4.12}, {21518085, "Choi_YH", "Physics", 3.85},
	{21319019, "Shin_DJ", "English", 3.21}, {21511053, "Ahn_SB", "CivilEng", 4.43} };
	strcpy(pST_DB->name, "Student DB");
	pST_DB->num_students = sizeof(students) / sizeof(Student);
	pST_DB->students = students;
	printf("Initial status of Student DB:\n");
	print_StudentDB(pST_DB); printf("\n");

	sorting_StudentDB(pST_DB, ID, IN);
	printf("After sorting students by increasing order of student ID:\n");
	print_StudentDB(pST_DB); printf("\n");

	sorting_StudentDB(pST_DB, MAJOR, IN);
	printf("After sorting students by increasing order of major:\n");
	print_StudentDB(pST_DB); printf("\n");

	sorting_StudentDB(pST_DB, GPA, DE);
	printf("After sorting students by decreasing order of GPA:\n");
	print_StudentDB(pST_DB); printf("\n");

	sorting_StudentDB(pST_DB, NAME, IN);
	printf("After sorting students by increasing order of student name:\n");
	print_StudentDB(pST_DB); printf("\n");

}