/*
Multi_thread.cpp
Date : 2026-05-21
Author : Lee Jong Kwang
- 스레드 기능 활용을 위한 문자 출력 기능 
*/

#include <iostream>
#include <Windows.h>
#include "Multi_Thread.h"

/* 문자를 출력하는 기능 */
void simpleThread(ThreadParam* pThrdParam) {
	std::string threadName = pThrdParam->name;
	char myMark = pThrdParam->myMark;
	std::mutex* pMTX_cs = pThrdParam->pMTX_cs;
	char* pTurn = pThrdParam->pTurn;
	for (int i = 0; i < 10; i++) {
		while (*pTurn != myMark)
			Sleep(1); 

		/* 다른 스레드 접근 금지 기능 */
		pMTX_cs->lock();
		std::cout << threadName << " :: ";

		for (int j = 0; j < 50; j++)
			std::cout << myMark;

		std::cout << std::endl;
		/* 잠금 해제 */
		pMTX_cs->unlock();

		/* 스레드 순서 검사 */
		if (myMark == ('A' + NUM_THREADS - 1))
			*pTurn = 'M';
		else
			*pTurn = myMark + 1;

		Sleep(1);
	}
}