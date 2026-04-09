#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME_LENGTH 60
#define MAX_MAJOR_LENGTH 20

typedef struct Student {
	int id;
	char name[MAX_NAME_LENGTH];
	char major[MAX_MAJOR_LENGTH];
	double GPA;
};

typedef struct StudentDB {
	char name[64];
	int num_students;
	Student* students;
};
enum ST_STANDARD { ID, NAME, MAJOR, GPA };
enum SORT_MODE { IN, DE };

void print_Student(StudentDB* db);
void print_StudentDB(StudentDB* db);

int compare_Student(Student* a, Student* b, ST_STANDARD standard, SORT_MODE mode);
void sorting_StudentDB(StudentDB* db, ST_STANDARD standard, SORT_MODE mode);