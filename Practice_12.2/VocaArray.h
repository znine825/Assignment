/*
VocaArray.h
Date : 2026-06-05
Author : Lee Jong Kwang
- 단어 배열과 관련된 정보를 저장하기 위한 클래스 정의
*/

#ifndef VOCA_ARRAY_H
#define VOCA_ARRAY_H
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <regex>
#include "Voca.h"

/* 클래스 VocaArray */
class VocaArray {
public:
	/* 매개변수 생성자 */
	VocaArray(std::ifstream&); 
	/* 기본 생성자 */
	VocaArray() { 
		this->array_voca.clear();
		this->num_vocas = 0;
	}
	/* 소멸자 */
	~VocaArray() {  
		this->array_voca.clear();
	}
	/* num_vocas 반환 */
	//int size() { return num_vocas; }
	/* 배열 구현을 위한 [] 오버로딩 */
	Voca& operator[](int index);
	/* 배열 출력 */
	void printVocaArray(std::ostream& fout);
	/* 파일에서 단어 배열을 읽어서 저장하는 함수 */
	int fgetVocaArray(std::istream& fin);
	/* num_vocas 반환 */
	int getNumVocas() { return num_vocas; }
private:
	std::string db_name;
	bool _isValidIndex(int index);
	int num_vocas;
	std::vector<Voca> array_voca;
};

/* 매개변수 생성자 */
VocaArray::VocaArray(std::ifstream& fin) {
	int num_vocas;
	getline(fin, this->db_name);  
	num_vocas = this->fgetVocaArray(fin);
	this->num_vocas = num_vocas;
}
/* 배열 구현을 위한 [] 오버로딩 */
Voca& VocaArray::operator[](int index) {
	if (_isValidIndex(index))
		return this->array_voca[index];
	else {
		throw std::out_of_range("VocaArray index out of range");
	}
}

/* 배열 출력 */
void VocaArray::printVocaArray(std::ostream& fout) {
	fout << this->db_name << "(num_vocas : " << this->num_vocas << ")" << std::endl;
	for (int i = 0; i < this->num_vocas; i++) {
		fout << this->array_voca[i];
		fout << std::endl;
	}
}

/* 유효한 인덱스인지 확인하는 함수 */
bool VocaArray::_isValidIndex(int index) {
	if ((index < 0) || (index >= num_vocas))
		return false;
	else
		return true;
}

/* 리스트 출력 */
void printList(const std::list<std::string>& values) {
	for (const std::string& value : values)
	{
		std::cout << " - " << value << std::endl;
	}
}

/* 파일에서 단어 배열을 읽어서 저장하는 함수 */
int VocaArray::fgetVocaArray(std::istream& fin) {
	std::string db_name, strLine;
	int num_vocas = 0;
	while (getline(fin, strLine)) {
		Voca voca;
		if (voca.fgetVoca(strLine)) {
			array_voca.push_back(voca);
			num_vocas++;
		}
		else {
			std::cout << "Parsing failed: " << strLine << std::endl;
		}
	}
	return num_vocas;
}

#endif