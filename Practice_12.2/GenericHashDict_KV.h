/*
GenericHashDict_KV.h
Date : 2026-06-05
Author : Lee Jong Kwang
- KV를 저장하기위한 Hash Dictionary 클래스 정의
*/

#ifndef HASH_DICTIONARY_H
#define HASH_DICTIONARY_H
#include "GenericHashMap_KV.h"
#define DEFAULT_HASH_SIZE 101

/* 클래스 GenericHashDict_KV */
template <typename K, typename V>
class GenericHashDict_KV : public GenericHashMap_KV<K, V> {
public:  
	typedef typename GenericHashMap_KV<K, V>::Iterator Iterator;
	typedef typename GenericHashMap_KV<K, V>::BItor BItor;
	int fgetVocaDict(std::istream& fin);
	/* 클래스 Range */
	class Range {  
	private:
		Iterator _begin;  
		Iterator _end; 
	public:
		Range() = default; 
		Range(const Iterator& b, const Iterator& e) 
			: _begin(b), _end(e) {
		}
		Iterator begin() { return _begin; }  
		Iterator end() { return _end; }  
	};
public:  
	/* 매개변수 생성자 */
	GenericHashDict_KV(const std::string nm,
		int hashTblSize = DEFAULT_HASH_SIZE)
		: GenericHashMap_KV<K, V>(nm, hashTblSize) {} 
	/* 객체 삽입 */
	Iterator insert(const K& k, const V& v)  {
		Iterator p = this->_find(k);
		BItor bkt = p.getBkt();
		Iterator itrEnd = Iterator(this->BA, bkt, bkt->end());
		while ((p != itrEnd) && ((*p).key() == k)) {
			GenericHashMap_KV<K, V>::_next(p);
		}
		return this->_insert(p, Entry_KV<K, V>(k, v));
	}

	/* key k로 객체 삭제 */
	Range findAll(const K& k) {
		Iterator b = this->_find(k);
		if (GenericHashMap_KV<K, V>::endOfBkt(b)) {
			return Range(this->end(), this->end());
		}
		Iterator p = b;
		BItor bkt = p.getBkt();
		Iterator itrEnd = Iterator(this->BA, bkt, bkt->end());
		while ((p != itrEnd) && ((*p).key() == k)) {
			GenericHashMap_KV<K, V>::_next(p);  
		}
		if (p == itrEnd) {
			++bkt;
			while (bkt != this->BA.end() && bkt->empty()) {
				++bkt;
			}
			if (bkt == this->BA.end()) {
				p = this->end();
			}
			else {
				p = Iterator(this->BA, bkt, bkt->begin());
			}
		}
		return Range(b, p);
	}
};

/* 파일에 저장된 VocaDict 불러오기*/
template <typename K, typename V>
int GenericHashDict_KV<K, V>::fgetVocaDict(std::istream& fin)
{
	std::string strLine;
	int num_vocas = 0;
	fin >> this->name;
	getline(fin, strLine);  
	while (getline(fin, strLine)) {
		Voca voca;
		if (voca.fgetVoca(strLine)) {
			insert(voca.getKeyWord(), voca);
		}
		else {
			std::cout << "Parsing failed: " << strLine << std::endl;
		}
		num_vocas++;
	}
	return num_vocas;
}
#endif