/*
GenericCirQ.h
Date : 2026-05-22
Author : Lee Jong Kwang
- 환형큐 구현 기능 
*/

#ifndef GENERIC_CIRQ_H
#define GENERIC_CIRQ_H
#include <iostream>
#include <thread>
#include <mutex>


/* 전방 선언 */
template<typename T>
class GenericCirQ;
template<typename T>
std::ostream& operator<<(std::ostream& fout, const GenericCirQ<T>& CirQ);

/* 클래스 GenericCirQ */
template<typename T>
class GenericCirQ {
	/* 출력을 위한 <<연산자 오버로딩 */
	friend std::ostream& operator<<(std::ostream& fout, const GenericCirQ<T>& CirQ) {
		fout << CirQ.name << "(capacity= " << CirQ.capacity;
		fout << ", current num_elements = " << CirQ.num_elements << ") : ";
		if (CirQ.num_elements <= 0) {
			fout << "CirQ is empty now !!" << std::endl;
		}
		else {
			int index = 0;
			for (int i = 0; i < CirQ.num_elements; i++) {
				index = CirQ.front + i;
				if (index >= CirQ.capacity)
					index = index % CirQ.capacity;
				fout << CirQ.GA[index];
				if (i != CirQ.num_elements - 1)
					fout << ", ";
				if ((i + 1) % 10 == 0)
					fout << std::endl;
			}
			fout << std::endl;
		}
		return fout;
	}

public:
	/* 메게변수 생성자 */
	GenericCirQ(std::string nm, int capa) { 
		this->name = nm;
		this->GA = new T[capa]();
		if (this->GA == NULL) {
			std::cout << "Error in creation of dynamic array GA !!" << std::endl;
			exit(-1);
		}
		this->capacity = capa;
		this->front = 0;
		this->back = -1;
		this->num_elements = 0;
	}
	/* 소멸자 */
	~GenericCirQ() {
		delete[] GA;
	} 
	/* 큐 제거 */
	T* dequeue(); 
	/* 큐 추가*/
	T* enqueue(const T element); 
	/* 비어있는지 확인 */
	bool isEmpty() { return (this->num_elements == 0); }
	/* 가득 차있는지 확인 */
	bool isFull() { return (this->num_elements >= this->capacity); }
	/* 큐 개수 반환 */
	int getNumElements() { return this->num_elements; }

private:
	std::string name;
	T* GA;
	int num_elements;
	int capacity;  
	int front;  
	int back;  
	std::mutex mtx_criQ;
};

/* 큐 생성 */
template<typename T>
T* GenericCirQ<T>::enqueue(const T element)
{
	T* pE;
	if (this->isFull())
	{
		std::cout << "Queue is Full !!" << std::endl;
		return NULL;
	} this->mtx_criQ.lock();
	this->back++;
	if (this->back >= this->capacity) {
		this->back = this->back % this->capacity;
	} this->GA[this->back] =
		element;
	pE = &this->GA[this->back];
	this->num_elements++;
	this->mtx_criQ.unlock();
	return pE;
}

/* 큐 제거*/
template<typename T>
T* GenericCirQ<T>::dequeue()
{
	T* pE;
	this->mtx_criQ.lock();
	if (isEmpty())
		return NULL;
	else {
		pE = &(this->GA[this->front]);
		this->front++;
		if (this->front >= this->capacity)
			this->front = this->front % this->capacity;
		this->num_elements--;
		this->mtx_criQ.unlock();
		return pE;
	}
}
#endif