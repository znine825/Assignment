/*
22312004 이종광
Student.h
2026-04-02
학생 구조체와와 DB정의 및 출력과 정렬을 위한 함수의 해더 파일
*/

#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME_LENGTH 60
#define MAX_MAJOR_LENGTH 20

// 학생 구조체 정의
typedef struct Student {
	int id;
	char name[MAX_NAME_LENGTH];
	char major[MAX_MAJOR_LENGTH];
	double GPA;
};

// 학생 데이터베이스 구조체 정의
typedef struct StudentDB {
	char name[64];
	int num_students;
	Student* students;
};

StudentDB* fgetStudentDB(FILE* fin);


// 학생 정렬 기준과 정렬 모드 정의
enum ST_STANDARD { ID, NAME, MAJOR, GPA };
enum SORT_MODE { IN, DE };

// 학생 출력 함수
void print_Student(StudentDB* db);
// 학생 데이터베이스 출력 함수
void print_StudentDB(StudentDB* db);

void delete_StudentDB(StudentDB* db);

// 학생을 standard과 mode에 따라 비교하는 함수
int compare_Student(Student* a, Student* b, ST_STANDARD standard, SORT_MODE mode);
// 학생 데이터베이스를 standard과 mode에 따라 정렬하는 함수
void sorting_StudentDB(StudentDB* db, ST_STANDARD standard, SORT_MODE mode);