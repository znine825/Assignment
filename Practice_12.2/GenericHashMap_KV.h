/*
GenericHashMap_KV.h
Date : 2026-06-05
Author : Lee Jong Kwang
- KV를 저장하기위한 Hash Map 클래스 정의
*/

#ifndef GenericHashMap_KV_H
#define GenericHashMap_KV_H
#include <vector>
#include <list>
#include "Entry_KV.h"

/* 클래스 GenericHashMap_KV */
template <typename K, typename V>
class GenericHashMap_KV {
protected:  
	typedef std::list<Entry_KV<K, V>> Bucket;  
	typedef std::vector<Bucket> BktArray; 
	typedef typename BktArray::iterator BItor;  
	typedef typename Bucket::iterator EItor;  
protected:
	int num_entry;  
	BktArray BA;  
	std::string name;
public:  
	class Iterator;
public:
	/* 매개변수 생성자 */
	GenericHashMap_KV(std::string nm, int hashTblSize = 101);
	/* name 반환 */
	std::string getName() { return name; }
	/* size 반환 */
	int size() const;  
	/* empty 여부 반환 */
	bool empty() const;  
	/* key k를 찾아서 Iterator 반환 */
	Iterator find(const K& k);  
	/* key k와 value v를 삽입 */
	Iterator insert(const K& k, const V& v);
	/* key k로 객체 삭제 */
	void erase(const K& k);  
	/* Iterator로 객체 삭제 */
	void erase(const Iterator& p); 
	/* begin Iterator 반환 */
	Iterator begin();  
	/* end Iterator 반환 */
	Iterator end();  
	/* key k를 찾아서 Iterator 반환 하기위한 함수  */
	Iterator _find(const K& k);  
	/* key k와 value v를 삽입하기 위한 함수 */
	Iterator _insert(const Iterator& p, const Entry_KV<K, V>& e);
	/* 객체 삭제하기 위한 함수 */
	void _erase(const Iterator& p); 
	/* Iterator로 객체 삭제하기 위한 함수 */
	static void _next(Iterator& p) { ++p.ent; }  
	/* Iterator가 버킷의 끝인지 여부 반환 */
	static bool endOfBkt(const Iterator& p) { return p.ent == p.bkt->end(); }
	/* 버킷 크기 출력 */
	void fprintBucketSizes(std::ostream& fout);
	/* 버킷 인덱스 반환 */
	int getBucketIndex(const K& k) const { return static_cast<int>(std::hash<K>{}(k) % BA.size()); }
public:  
	 
	class Iterator {  
	private:
		EItor ent;  
		BItor bkt;  
		const BktArray* ba;  
	public:
		Iterator() {}  
		Iterator(const BktArray& a, const BItor& b, const EItor& q = EItor())
			: ent(q), bkt(b), ba(&a) {
		}
		EItor& getEntry_KV() { return ent; }
		BItor& getBkt() { return bkt; }
		Entry_KV<K, V>& operator*() { return *ent; }  
		bool operator==(const Iterator& p) const;  
		bool operator!=(const Iterator& p) const; 
		Iterator& operator++();  
		friend class GenericHashMap_KV;  
	};
};

/* 매개변수 생성자 */
template <typename K, typename V>
GenericHashMap_KV<K, V>::GenericHashMap_KV(std::string nm, int hashTblSize)
	: num_entry(0), BA(hashTblSize), name(nm) {}

/* begin Iterator 반환 */
template <typename K, typename V> 
typename GenericHashMap_KV<K, V>::Iterator
GenericHashMap_KV<K, V>::begin() {
	if (empty())
		return end();  
	BItor bkt = BA.begin(); 
	while (bkt->empty())
		++bkt;  
	return Iterator(BA, bkt, bkt->begin());  
}

/* end Iterator 반환 */
template <typename K, typename V>  
typename GenericHashMap_KV<K, V>::Iterator GenericHashMap_KV<K, V>::end() {
	return Iterator(BA, BA.end());
}

/* size 반환 */
template <typename K, typename V>  
int GenericHashMap_KV<K, V>::size() const { return num_entry; }

/* empty 여부 반환 */
template <typename K, typename V> 
bool GenericHashMap_KV<K, V>::empty() const { return size() == 0; }

/* key 를 찾아서 Iterator 반환 하기위한 함수  */
template <typename K, typename V>  
typename GenericHashMap_KV<K, V>::Iterator
GenericHashMap_KV<K, V>::_find(const K& k) {
	std::size_t hashValue = std::hash<K>{}(k) % BA.size();  
#ifdef HASH_TEST
	cout << setw(3) << hashValue;
#endif
	BItor bkt = BA.begin() + hashValue;  
	Iterator p(BA, bkt, bkt->begin());  
	Iterator end(BA, bkt, bkt->end());
	while ((p != end) && (*p).key() != k)  
		++p.ent;
	return p; 
}

/* key 를 찾아서 Iterator 반환*/
template <typename K, typename V> 
typename GenericHashMap_KV<K, V>::Iterator
GenericHashMap_KV<K, V>::find(const K& k) {
	Iterator p = _find(k);  
	if (endOfBkt(p))  
		return end();  
	else
		return p;  
}

/* key k와 value v를 삽입하기 위한 함수 */
template <typename K, typename V>  
typename GenericHashMap_KV<K, V>::Iterator
GenericHashMap_KV<K, V>::_insert(const Iterator& p,
	const Entry_KV<K, V>& e) {
	EItor ins = p.bkt->insert(p.ent, e);  
	num_entry++; 
	return Iterator(BA, p.bkt, ins);  
}

/* key k와 value v를 삽입 */
template <typename K, typename V>  
typename GenericHashMap_KV<K, V>::Iterator
GenericHashMap_KV<K, V>::insert(const K& k, const V& v) {
	Iterator p = _find(k);  
	if (endOfBkt(p)) {  
		return _insert(p, Entry_KV<K, V>(k, v)); 
	}
	else {  
		(p.getEntry_KV())->setValue(v);  
		return p;  
	}
}
/* 객체 삭제하기 위한 함수 */
template <typename K, typename V>  
void GenericHashMap_KV<K, V>::_erase(const Iterator& p) {
	p.bkt->erase(p.ent);  
	num_entry--;  
}

/* Iterator로 객체 삭제 */
template <typename K, typename V>  
void GenericHashMap_KV<K, V>::erase(const Iterator& p) {
	_erase(p);
}

/* key로 객체 삭제 */
template <typename K, typename V>  
void GenericHashMap_KV<K, V>::erase(const K& k) {
	Iterator p = _find(k);  
	if (endOfBkt(p)) {
		std::cout << "Error ::Erase of nonexistent !!\n";
	}
	else
		_erase(p);  
}

/* 비교를 위한 == 연산자 오버로딩 */
template <typename K, typename V>  
bool GenericHashMap_KV<K, V>::Iterator::operator==(const Iterator& p) const {
	if (ba != p.ba || bkt != p.bkt) return false;  
	else if (bkt == ba->end()) return true;  
	else return (ent == p.ent);  
}

/* 비교를 위한 != 연산자 오버로딩 */
template <typename K, typename V>  
bool GenericHashMap_KV<K, V>::Iterator::operator!=(const Iterator& p) const {
	if (ba != p.ba || bkt != p.bkt) return true;  
	else if (bkt == ba->end()) return false;  
	else return (ent != p.ent);  
}

/* ++ 연산자 오버로딩 */
template <typename K, typename V>  
typename GenericHashMap_KV<K, V>::Iterator&
GenericHashMap_KV<K, V>::Iterator::operator++() {
	++ent;  
	if (endOfBkt(*this)) {  
		++bkt;  
		while (bkt != ba->end() && bkt->empty())  
			++bkt;
		if (bkt == ba->end()) return *this; 
		ent = bkt->begin();  
	} return *this;  
}

/* 버킷 크기 출력 */
template <typename K, typename V>
void GenericHashMap_KV<K, V>::fprintBucketSizes(std::ostream& fout) {
	int bkt_size;
	int max_ent, min_ent, total;
	int num_bkts;
	double avg = 0.0;
	max_ent = min_ent = BA[0].size();
	total = 0;
	num_bkts = BA.size();
	for (int bkt = 0; bkt < num_bkts; bkt++) {
		bkt_size = BA[bkt].size();
		fout << "Bucket[" << std::setw(3) << bkt << "] : ";
			fout << bkt_size << " entries\n";
		if (bkt_size > max_ent)
			max_ent = bkt_size;
		if (bkt_size < min_ent)
			min_ent = bkt_size;
		total += bkt_size;
	}
	avg = static_cast<double>(total) / num_bkts;
	fout.precision(2);
	fout << "Max_ent (" << std::setw(2) << max_ent;
	fout << "), min_ent (" << std::setw(2) << min_ent;
	fout << "), avg (" << std::setw(5) << avg << ")\n";
}

#endif