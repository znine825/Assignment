/*
Practice_12.2.cpp
Date : 2026-06-05
Author : Lee Jong Kwang
- KV를 저장하기위한 Hash Map 클래스 정의
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include "Voca.h"
#include "VocaArray.h"
#include "GenericHashDict_KV.h"
#include <string>

using namespace std;
#define HASH_TABLE_SIZE 101

/* 메인 함수 */
int main() {
	ifstream fin;
	/* 파일  잘 열리는지 확인 */
	fin.open("myVoca_data.txt");
	if (fin.fail()) {
		cout << "Fail to open input data file (myVoca_data.txt) !!" << endl;
		exit(-1);
	}

	/* HashDict 객체 생성 */
	GenericHashDict_KV<std::string, Voca> thesHashDict("My Thesaurus Hash Map", HASH_TABLE_SIZE);
	GenericHashDict_KV<std::string, Voca>* pHashDict = &thesHashDict;
	GenericHashDict_KV<std::string, Voca>::Iterator vocaHD_Iter;
	GenericHashDict_KV<std::string, Voca>::Range vocaHD_Range;

	/* 파일에서 단어 불러오기 */
	pHashDict->fgetVocaDict(fin);
	cout << "\n==============================================\n";
	cout << "Voca HashMap after fgetVocaDict() :" << endl;
	string keyWord;
	Voca* pVoca, voca;
	Entry_KV<string, Voca> vocaEntry_KV;
	vocaHD_Iter = pHashDict->begin();

	/* HashDict의 모든 항목 출력 */
	while (vocaHD_Iter != pHashDict->end()) {
		vocaEntry_KV = *vocaHD_Iter;
		keyWord = vocaEntry_KV.getKey();
		voca = vocaEntry_KV.getValue();
		cout << keyWord << " : " << voca << endl;
		++vocaHD_Iter;
	}
	
	/* 버킷 크기 출력 */
	pHashDict->fprintBucketSizes(cout);
	cout << "\nTesting keyword findings in HashDict_Voca ...." << endl;
	std::string test_keywords[] = { "mean", "compromise", "duplicate" };
	/* 테스트 키워드로 HashDict에서 항목 찾기 */
	for (auto keyWord : test_keywords) {
		cout << "Thesaurus of " << keyWord << " in HashDict_Voca : \n";
		vocaHD_Range = pHashDict->findAll(keyWord);
		for (vocaHD_Iter = vocaHD_Range.begin();
			vocaHD_Iter != vocaHD_Range.end(); ++vocaHD_Iter) {
			voca = (*vocaHD_Iter).getValue();
			cout << voca << endl;
		}
	}
	return 0;
}