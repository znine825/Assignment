/*
Practice_09.1.cpp
Date : 2026-05-15
Author : Lee Jong Kwang
- Verification of stack addition and removal functions using a circular queue
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "GenericCirQ.h"

using namespace std;
#define NUM_ELEMENTS_PER_ROUND 7
#define QUEUE_CACITY 10

/* 메인 함수 */
int main(void) {
	GenericCirQ<int> genericIntCirQ("GenericIntCirQ", QUEUE_CACITY);
	int data = 0;
	int* pE;
	for (int j = 0; j < 4; j++) {
		/* 큐 추가 */
		for (int i = 0; i < NUM_ELEMENTS_PER_ROUND; i++) {
			cout << "EnCirQ (" << setw(3) << data << ") => ";
			genericIntCirQ.enqueue(data);
			cout << genericIntCirQ;
			data++;
		}
		/* 큐 제거 */
		for (int i = 0; i < NUM_ELEMENTS_PER_ROUND; i++) {
			cout << "DeCirQ (";
			pE = genericIntCirQ.dequeue();
			cout << setw(3) << *pE << ") => ";
			cout << genericIntCirQ;
		}
	}
}