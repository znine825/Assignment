/*
GenericCirQ.h
Date : 2026-05-15
Author : Lee Jong Kwang
- Circular Queue Class Implementation
*/

#include <string>
#include "GenericArray.h"

/* 전방 선언 */
template<typename T>
class GenericCirQ;
template<typename T>
std::ostream& operator<<(std::ostream&, const GenericCirQ<T>&);

/* 클래스 GenericCirQ */
template<class T>
class GenericCirQ : public GenericArray<T> {
	/* 출력을 위한 << 연산자 오버로딩 */
	template<class T>
	friend std::ostream& operator<<(std::ostream&, const GenericCirQ<T>&);

public:
	/* 생성자 */
	GenericCirQ();
	/* 매게변수 생성자 */
	GenericCirQ(std::string nm, int capacity);
	/* 소멸자 */
	~GenericCirQ();

	/* 큐 삭제 */
	T* dequeue(); 
	/* 큐 추가 */
	T* enqueue(const T element); 

	/* 비어있는지 확인 */
	bool isEmpty() { return (this->num_elements == 0); }
	/* 꽉 차있는지 확인 */
	bool isFull() { return (this->num_elements >= this->capacity); }
	/* 크기를 반환 */
	int size() { return this->num_elements; }
	/* 출력 기능 */
	void fprint(std::ostream& fout, int elements_per_line);

private:
	int front; // front index of Circular Queue
	int back; // back index of Circular Queue
};

/* 생성자 */
template<class T>
GenericCirQ<T>::GenericCirQ() {
	this->front = 0;
	this->back = 0;
}

/* 매게변수 생성자 */
template<class T>
GenericCirQ<T>::GenericCirQ(std::string nm, int capacity)
	: GenericArray<T>(nm, capacity) {
}

/* 소멸자 */
template<class T>
GenericCirQ<T>::~GenericCirQ() {
}

/* 큐 삭제 */
template<class T>
T* GenericCirQ<T>::dequeue() {
	T* result;
	/* 비어있는지 확인 */
	if (this->isEmpty()) {
		std::cout << "Queue is Empty !" << std::endl;
		return NULL;
	}
	else {
		/* 제거될 원소 저장 */
		result = &this->GA[this->front];
		this->front++;
		/* front가 끝을 지났을 때 처음으로 보내기 */
		if (this->front >= this->capacity) {
			this->front = this->front % this->capacity;
		}
		this->num_elements--;
		return result;
	}
}

/* 큐 추가 */
template<class T>
T* GenericCirQ<T>::enqueue(const T element) {
	T* result;
	/* 꽉 차있는지 확인 */
	if (this->isFull()) {
		std::cout << "Queue is Full !" << std::endl;
		return NULL;
	}
	else {
		/* back가 끝을 지났을 떄 처음으로 보내기 */
		if (this->back >= this->capacity) {
			this->back = this->back % this->capacity;
		}

		this->GA[this->back] =element;

		this->back++;
		/* 추가된 원소 저장 */
		result = &this->GA[this->back];

		this->num_elements++;
		return result;
	}
}

/* 출력을 위한 << 연산자 오버로딩 */
template<class T>
std::ostream& operator<<(std::ostream& fout, const GenericCirQ<T>& CirQ) {
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