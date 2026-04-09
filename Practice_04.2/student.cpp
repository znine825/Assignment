#include <stdio.h>
#include <string.h>
#include "Student.h"

void print_Student(Student* db) {
	printf("Student [st_ID: %8d, st_NAME: %10s, Major: %10s, GPA: %7f]\n",
		db->id, db->name, db->major, db->GPA);
}
void print_StudentDB(StudentDB* db) {
	printf("StudentDB :\n");
	for (int i = 0; i < db->num_students; i++) {
		print_Student(&db->students[i]);
	}
}

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
void sorting_StudentDB(StudentDB* db, ST_STANDARD standard, SORT_MODE mode) {
	int size = db->num_students;
	for (int i = 1; i < size; i++) {
		Student key = db->students[i];
		int j = i - 1;

		while (j >= 0 && compare_Student(&db->students[j], &key, standard, mode) > 0) {
			db->students[j + 1] = db->students[j];
			j--;
		}
		db->students[j + 1] = key;
	}
}