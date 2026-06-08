/*
GenericArray.h
Date : 2026-05-15
Author : Lee Jong Kwang
- Implement GenericArray, a class that can manage various data types using class templates.
- Implementation of data creation, shuffling, and sorting functions
*/

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/* 전방 선언 */
template<typename T>
class GenericArray;
template<typename T>
std::istream& operator>>(std::istream& fin, GenericArray<T>& ga);
template<typename T>
std::ostream& operator<<(std::ostream& fout, const GenericArray<T>& ga);

/* 클래스 GenericArray */
template<class T>
class GenericArray {
	template<class T>
	/* 입력을 위한 >> 연산자 오버로딩 */
	friend std::istream& operator>>(std::istream& fin, GenericArray<T>& ga);
	template<class T>
	/* 출력을 위한 << 연산자 오버로딩 */
	friend std::ostream& operator<<(std::ostream& fout, const GenericArray<T>& ga);

public:
	/* 생성자 */
	GenericArray();
	/* 매게변수 생성자 */
	GenericArray(std::string nm, int capacity);
	/* 소멸자 */
	~GenericArray();
	/* 큰 랜덤 배열 생성 기능 */
	void genBigRandArray(int size, T offset);
	/* 배열의 개수를 바꾸는 기능 */
	void setNumElements(int num_elements) { this->num_elements = num_elements; }
	/* 배열을 섞어주는 기능 */
	void shuffle();
	/* 배열의 삽입 정렬 기능 */
	void insertSort();
	/* 배열을 보기 좋게 출력해주는 기능 */
	void printArray(int per_line, int sample_lines);
	/* 배열을 반환하는 기능 */
	T* getGA() { return GA; }

protected:
	std::string name;
	T* GA;
	int num_elements;
	int capacity;
};

/* 생성자 */
template<class T>
GenericArray<T>::GenericArray() {
	this->name = "Generic Array";
	this->GA = nullptr;
	this->num_elements = 0;
	this->capacity = 0;
}

/* 매게변수 생성자 */
template<class T>
GenericArray<T>::GenericArray(std::string nm, int capacity) {
	this->name = nm;
	this->GA = new T[capacity];
	this->num_elements = 0;
	this->capacity = capacity;
}

/* 소멸자 */
template<class T>
GenericArray<T>::~GenericArray() {
	delete[] this->GA;
}

/* 큰 랜덤 배열 생성 기능 */
template<class T>
void GenericArray<T>::genBigRandArray(int size, T offset) {
	if (GA != nullptr) {
		delete[] this->GA;
	}
	this->GA = new T[size];
	for (int i = 0; i < size; i++) {
		this->GA[i] = (T)(i + offset);
	}
	this->num_elements = size;
	shuffle();
}

/* 배열을 섞어주는 기능 */
template<class T>
void GenericArray<T>::shuffle() {
	int temp, rand_index;
	unsigned int u_int30 = 0;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < this->num_elements; i++) {
		u_int30 = ((long)rand() << 15) | rand();
		temp = u_int30 % this->num_elements;

		if (i != temp) {
			rand_index = this->GA[i];
			this->GA[i] = this->GA[temp];
			this->GA[temp] = rand_index;
		}
	}
}

/* 배열의 삽입 정렬 기능 */
template<class T>
void GenericArray<T>::insertSort() {
	for (int i = 1; i < this->num_elements; i++) {
		T key = this->GA[i];
		int j = i - 1;

		while (j >= 0 && this->GA[j] > key) {
			this->GA[j + 1] = this->GA[j];
			j--;
		}
		this->GA[j + 1] = key;
	}
}

/* 배열을 보기 좋게 출력해주는 기능 */
template<typename T>
void GenericArray<T>::printArray(int per_line, int sample_lines) {
	int count = 0;
	int block_size = per_line * sample_lines;
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	for (int i = 0; (i < block_size) && (count < this->num_elements); i++) {
		cout << setw(9) << this->GA[count];
		if (count >= this->num_elements)
			break;
		if ((i + 1) % per_line == 0)
			cout << endl;
		count++;
	}
	if (count >= this->num_elements)
		return;
	if ((this->num_elements - block_size) > count) {
		count = this->num_elements - block_size;
		cout << " ...... " << endl;
	}
	for (int i = 0; (i < block_size) && (count < this->num_elements); i++) {
		cout << setw(9) << this->GA[count];
		if (count >= this->num_elements)
			break;
		if ((i + 1) % per_line == 0)
			cout << endl;
		count++;
	}
}

/* 입력을 위한 >> 연산자 오버로딩 */
template<typename T>
std::istream& operator>>(std::istream& fin, GenericArray<T>& ga) {
	string nm;
	int num_elements;
	T data;
	fin >> nm >> num_elements;
	ga.name = nm;
	ga.num_elements = num_elements;
	if (num_elements > ga.capacity) {
		delete[] ga.GA;
		ga.GA = new T[ga.num_elements]();
		ga.capacity = num_elements;
	}
	for (int i = 0; i < num_elements; i++) {
		fin >> data;
		ga.GA[i] = data;
	} return fin;
}

/* 출력을 위한 << 연산자 오버로딩 */
template<typename T>
std::ostream& operator<<(std::ostream& fout, const GenericArray<T>& ga) {
	fout << ga.name << "(num_elements = " << ga.num_elements << ") = ";
	for (int i = 0; i < ga.num_elements; i++) {
		fout << ga.GA[i];
		if (i != ga.num_elements - 1)
			fout << ", ";
		if ((i + 1) % 10 == 0)
			fout << endl;
	}
	fout << endl;
	return fout;
}