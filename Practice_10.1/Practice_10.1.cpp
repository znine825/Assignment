/*
Practice_10.1.cpp
Date : 2026-05-21
Author : Lee Jong Kwang
- 멀티스레드 기능 활용
- 출력이 중복되지 않도록 mutex 기능 활용
- A B C M 을 50개를 10 줄씩 각각 출력
*/

#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <Windows.h> 
#include "Multi_Thread.h" 

int main(void) {
	std::mutex mtx_console;
	/* 어떤 스레드 차례인지 저장 */
	char turn = 'M';
	ThreadParam thrdParams[NUM_THREADS];
	std::thread::id threadIDs[NUM_THREADS];
	std::thread simThrds[NUM_THREADS];

	/* Thread 추가하기 */
	for (int i = 0; i < NUM_THREADS; i++) {
		thrdParams[i].name = std::string("Thread_") + (char)('A' + i);
		thrdParams[i].myMark = 'A' + i;
		thrdParams[i].pMTX_cs = &mtx_console;
		/* 모든 스레드가 같은 turn 변수를 공유하게 됨 */
		thrdParams[i].pTurn = &turn;
		/* 스레드 추가 및 실행 */
		simThrds[i] = std::thread(simpleThread, &thrdParams[i]);
		threadIDs[i] = simThrds[i].get_id();
		/* 한번에 한 스래드만 출력하기 */
		mtx_console.lock();
		std::cout << "main() : Thread (" << thrdParams[i].name;
		std::cout << ", id: " << threadIDs[i];
		std::cout << ") is successfully created, now !!" << std::endl;
		/* 잠금 해제 */
		mtx_console.unlock();
	}

	/* 한번에 한 스래드만 출력하기 */
	mtx_console.lock();
	std::cout << "main() : Waiting the threads (";
	for (int i = 0; i < NUM_THREADS; i++) {
		std::cout << threadIDs[i] << ", ";
	}
	std::cout << ") to terminate by themselves ..." << std::endl;
	std::cout << "main() is working as a thread, now ..." << std::endl;
	/* 잠금 해제 */
	mtx_console.unlock();

	/* M차례가 올때까지 기다리기 */
	for (int i = 0; i < 10; i++) {
		while (turn != 'M')
			Sleep(1);

		mtx_console.lock();
		std::cout << "mainThrdM:: ";
		for (int j = 0; j < 50; j++)
			std::cout << 'M';
		std::cout << std::endl;
		mtx_console.unlock();
		turn = 'A';
		Sleep(1); // sleep 1000 ms
	}

	/* 다 끝날 때 까지 기다리기 */
	for (int i = 0; i < NUM_THREADS; i++) {
		simThrds[i].join();
	}
	mtx_console.lock();
	std::cout << "main() :: threads (";

	/* 끝난 Thread id 출력 */
	for (int i = 0; i < NUM_THREADS; i++) {
		std::cout << threadIDs[i] << ", ";
	}
	std::cout << ") are terminated, now." << std::endl;
	mtx_console.unlock();

	return 0;
} 