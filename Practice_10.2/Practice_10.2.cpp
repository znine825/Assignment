/*
Practice_10.2.cpp
Date : 2026-05-21
Author : Lee Jong Kwang
- Event Generator / Event Handler 멀티스레드 시뮬레이션
- Circular Queue를 이용한 Event 처리
*/

#include <iostream>
#include <Windows.h>
#include <thread>
#include <mutex>
#include "Multi_Thread.h"
#include "GenericCirQ.h"
#include "Event.h"
#include "SimParams.h"
#include <time.h>

using namespace std;

/* 메인 함수 */
void main() {

	/* 성능 측정용 변수 */
	LARGE_INTEGER QP_freq;
	double elapsed_time, min_elapsed_time, max_elapsed_time;
	double avg_elapsed_time, total_elapsed_time;

	/* Event 저장용 Circular Queue */
	GenericCirQ<Event> cirQ_Event("CirQ_Ev", CIRQ_CAPACITY);

	/* Event 및 Thread 관련 변수 */
	Event* pEvent, * pEv_min_elasped_time, * pEv_max_elapsed_time;
	int myAddr = 0;
	int event_handler_addr, eventPriority;

	/* Event Generator / Handler용 Thread Parameter */
	ThreadParam_Event thrdParam_EventGen, thrdParam_EventHndlr;

	/* Thread 동기화용 mutex */
	mutex cs_main, cs_thrd_mon;

	/* Thread 상태 모니터 */
	ThreadStatusMonitor thrdMon;

	/* Thread 실행 상태 플래그 */
	THREAD_FLAG eventThreadFlag = RUN;

	/* 상태 출력용 변수 */
	int count, numEventGenerated, numEventProcessed;
	int num_events_in_PrioQ;

	QueryPerformanceFrequency(&QP_freq);
	srand(time(NULL));

	/* 모니터 정보 초기화 */
	thrdMon.pFlagThreadTerminate = &eventThreadFlag;
	thrdMon.totalEventGenerated = 0;
	thrdMon.totalEventProcessed = 0;

	/* 처리 완료 Event 배열 초기화 */
	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++)
	{
		thrdMon.eventProcessed[ev].setEventNo(-1);
		thrdMon.eventProcessed[ev].setEventPri(-1);
	}

	/* Event Handler Thread 생성 및 설정  */
	thrdMon.numEventProcessed[myAddr] = 0;
	thrdParam_EventHndlr.role = EVENT_HANDLER;
	thrdParam_EventHndlr.myAddr = myAddr;
	thrdParam_EventHndlr.pCS_main = &cs_main;
	thrdParam_EventHndlr.pCS_thrd_mon = &cs_thrd_mon;
	thrdParam_EventHndlr.pCirQ_Event = &cirQ_Event;
	thrdParam_EventHndlr.maxRound = MAX_ROUND;
	thrdParam_EventHndlr.QP_freq = QP_freq;
	thrdParam_EventHndlr.pThrdMon = &thrdMon;

	/* Event 처리 스레드 실행 */
	thread thrd_EvProc(EventProc, &thrdParam_EventHndlr);

	cs_main.lock();
	std::cout << "Thread_EventProc is created and activated ..." << std::endl;
	cs_main.unlock();

	/* Event Generator Thread 생성 및 설정 */
	thrdMon.numEventGenerated[myAddr] = 0;
	thrdParam_EventGen.role = EVENT_GENERATOR;
	thrdParam_EventGen.myAddr = myAddr;
	thrdParam_EventGen.pCS_main = &cs_main;
	thrdParam_EventGen.pCS_thrd_mon = &cs_thrd_mon;
	thrdParam_EventGen.pCirQ_Event = &cirQ_Event;
	thrdParam_EventGen.targetEventGen = NUM_EVENTS_PER_GEN;
	thrdParam_EventGen.maxRound = MAX_ROUND;
	thrdParam_EventGen.QP_freq = QP_freq;
	thrdParam_EventGen.pThrdMon = &thrdMon;

	/* Event 생성 스레드 실행 */
	thread thrd_EvGen(EventGen, &thrdParam_EventGen);

	cs_main.lock();
	std::cout << "Thread_EventGen is created and activated ..."
		<< std::endl;
	cs_main.unlock();

	/* Main Thread 모니터링 루프 */
	for (int round = 0; round < MAX_ROUND; round++) {

		cs_main.lock();
		std::cout << endl << "==========================================" << std::endl;
		std::cout << "Thread monitoring by main() :: ";
		std::cout << " round(" << std::setw(2) << round << "): current total_event_gen(";
		std::cout << std::setw(2) << thrdMon.totalEventGenerated << "), total_event_proc(";
		std::cout << std::setw(2) << thrdMon.totalEventProcessed << ")" << std::endl;

		/* Event 출력 */
		numEventGenerated = thrdMon.numEventGenerated[0];
		std::cout << "Events generated (current total = " << std::setw(2) << numEventGenerated << ") :" << std::endl;
		printEvents(std::cout, thrdMon.eventGenerated, thrdMon.numEventGenerated[0], 10);

		/* Queue 상태 출력 */
		num_events_in_PrioQ = cirQ_Event.getNumElements();
		std::cout << "Events currently in CirQ ( total = " << num_events_in_PrioQ << ") :" << endl;
		std::cout << cirQ_Event << std::endl;

		/* 처리 완료 Event 출력 */
		numEventProcessed = thrdMon.totalEventProcessed;
		std::cout << "Events processed (current total = " << numEventProcessed << ") :" << std::endl;
		printEvents(std::cout, thrdMon.eventProcessed, thrdMon.numEventProcessed[0], 10);

		/* 모든 Event 종료 */
		if (numEventProcessed >= TOTAL_NUM_EVENTS) {
			eventThreadFlag = TERMINATE;
			cs_main.unlock();
			break;
		}
		cs_main.unlock();
		Sleep(100);
	}
	thrd_EvProc.join();
	thrd_EvGen.join();
}