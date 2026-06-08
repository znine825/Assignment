/*
Entry_KV.h
Date : 2026-06-05
Author : Lee Jong Kwang
- KV를 저장하기위한 클래스 정의
*/

#ifndef ENTRY_H
#define ENTRY_H
#include <iostream>
#include <iomanip>
#include <string>

/* 클래스 Entry_KV*/
template <typename K, typename V>
class Entry_KV { 
	/* 출력을 위한 << 오버로딩 */
	friend std::ostream& operator<<(std::ostream& fout, const Entry_KV& ent) {
		fout.setf(std::ios::left);
		fout << " Entry_KV [key: " << std::setw(8) << ent.key();
		fout.unsetf(std::ios::left);
		fout << ", value{" << ent.value() << "} ]";
		return fout;
	}
public: 
	/* 기본 생성자 */
	Entry_KV() {}  
	/* 매개변수 생성자 */
	Entry_KV(K key, V value) {
		setKey(key);
		setValue(value);
	}
	/* key 주소를 반환 */
	const K& key() const { return _key; } 
	/* Valeue 주소를 반환 */
	const V& value() const { return _value; } 
	/* Key를 설정 */
	void setKey(K k) { _key = k; }  
	/* Value를 설정 */
	void setValue(V v) { _value = v; }  
	/* Key를 반환 */
	K getKey() { return _key; }
	/* Value를 반환 */
	V getValue() { return _value; }
	/* 대입을 위한 = 연산자 오버로딩 */
	Entry_KV& operator=(Entry_KV right) {
		setKey(right._key);
		setValue(right._value);
		return *this;
	}
private: 
	K _key;  
	V _value;  
};
#endif