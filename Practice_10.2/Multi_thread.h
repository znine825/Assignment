/*
Multi_thread.h
Date : 2026-05-22
Author : Lee Jong Kwang
- 멀티 스레드 기능 구현 
*/

#ifndef MULTI_THREAD_H
#define MULTI_THREAD_H
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <thread>
#include <mutex>
#include <process.h>
#include <string>
#include "GenericCirQ.h"
#include "Event.h"
#include "SimParams.h"

#define NUM_GEN 1
#define NUM_HND 1
enum ROLE { EVENT_GENERATOR, EVENT_HANDLER };
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };

/* 스레트 상태 확인을 위한 구조체 */
typedef struct ThreadStatusMonitor {
	int numEventGenerated[NUM_GEN];
	int numEventProcessed[NUM_HND];
	int totalEventGenerated;
	int totalEventProcessed; 
	Event eventGenerated[TOTAL_NUM_EVENTS];
	Event eventProcessed[TOTAL_NUM_EVENTS];
	THREAD_FLAG* pFlagThreadTerminate;
};

/* 스레트 이벤트 정보저장을 위한 구조체 */
typedef struct ThreadParam_Event {
	std::mutex* pCS_main;
	std::mutex* pCS_thrd_mon;
	GenericCirQ<Event>* pCirQ_Event;
	FILE* fout;
	ROLE role;
	int myAddr;
	int maxRound;
	int targetEventGen;
	LARGE_INTEGER QP_freq; 
	ThreadStatusMonitor* pThrdMon;
};

void EventProc(ThreadParam_Event* pParam);
void EventGen(ThreadParam_Event* pParam);
#endif