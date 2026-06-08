/*
Multi_thread.h
Date : 2026-05-21
Author : Lee Jong Kwang
- 스레드 구조체 정의 기능
*/

#ifndef MULTI_THREAD_H
#define MULTI_THREAD_H
#include <thread>
#include <mutex>
#include <string>
#define NUM_THREADS 3

/* 스레드 구조체 정의 */
typedef struct ThreadParam {
	std::string name;
	char myMark;
	std::mutex* pMTX_cs;
	char* pTurn;
};

/* 문자를 출력하는 기능 */
void simpleThread(ThreadParam* pThrdParam);
#endif