/*
Event.cpp
Date : 2026-05-22
Author : Lee Jong Kwang
- 가상 이벤트 처리 기능
*/

#include <Windows.h>  
#include "GenericCirQ.h"
#include "Multi_Thread.h"
#include "Event.h"

using namespace std;

/* 가상 이벤트를 처리하는 기능 */
void EventProc(ThreadParam_Event* pParam) {
	/* 이벤트 처리에 필요한 변수 선언 */
	int maxRound;
	Event event, * pEv;
	int event_no = 0;
	int eventPriority = 0;
	int event_gen_count = 0, num_event_processed = 0;
	int targetEventGen;
	LARGE_INTEGER QP_freq, t_gen, t_proc;
	LONGLONG t_diff;
	double elapsed_time;
	ThreadParam_Event* pThrdParam = (ThreadParam_Event*)pParam;
	int myRole = pThrdParam->role;
	int myAddr = pThrdParam->myAddr;
	GenericCirQ<Event>* pCirQ_Event = pThrdParam->pCirQ_Event;
	ThreadStatusMonitor* pThrdMon = pThrdParam->pThrdMon;
	maxRound = pThrdParam->maxRound;
	QP_freq = pThrdParam->QP_freq;
	targetEventGen = pThrdParam->targetEventGen;

	for (int round = 0; round < maxRound; round++) {
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
			break;
		if (!pCirQ_Event->isEmpty())
		{
			pEv = pCirQ_Event->dequeue();
			event = *pEv;
			pThrdParam->pCS_thrd_mon->lock();
			//pThrdMon->ppEventsg[pThrdMon->numEventProcs] = pEvent;
			event.setEventHandlerAddr(myAddr);
			QueryPerformanceCounter(&t_proc);
			event.setEventProcTime(t_proc);
			t_gen = event.getEventGenTime();
			t_diff = t_proc.QuadPart - t_gen.QuadPart;
			elapsed_time = ((double)t_diff / QP_freq.QuadPart); // in second
			event.setEventElaspsedTime(elapsed_time * 1000); // in milli-second
			pThrdMon->eventProcessed[pThrdMon->totalEventProcessed] = event;
			pThrdMon->numEventProcessed[myAddr]++;
			pThrdMon->totalEventProcessed++;
			pThrdParam->pCS_thrd_mon->unlock();
		} // end if
		Sleep(100 + rand() % 100); // sleep in msec
	} // end for
}