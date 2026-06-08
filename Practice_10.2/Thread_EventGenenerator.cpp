/*
Event.cpp
Date : 2026-05-22
Author : Lee Jong Kwang
- 가상 이벤트 생성 기능 =
*/

#include <Windows.h>  
#include <format> 
#include "Multi_Thread.h"
#include "GenericCirQ.h"
#include "Event.h"
#include "SimParams.h"

/* 이벤트 생성 기능 */
void EventGen(ThreadParam_Event* pParam) {
	/* 이벤트 생성시 필요한 변수 선언 */
	ThreadParam_Event* pThrdParam;
	GenericCirQ<Event>* pCirQ_Event;
	int myRole;
	int maxRound;
	Event event, * pEv;
	std::string evt_no_str;
	std::string evt_name;

	/* 이벤트 정보 */
	int ev_no = 0;
	int ev_priority = 0;
	int ev_gen_count = 0;
	int targetEventGen;
	int myAddr = -1;
	int ev_gen_addr = 0;
	LARGE_INTEGER t_gen;
	ThreadStatusMonitor* pThrdMon;
	pThrdParam = (ThreadParam_Event*)pParam;
	myRole = pThrdParam->role;
	myAddr = pThrdParam->myAddr;
	pCirQ_Event = pThrdParam->pCirQ_Event;
	pThrdMon = pThrdParam->pThrdMon;
	maxRound = pThrdParam->maxRound;
	targetEventGen = pThrdParam->targetEventGen;

	for (int round = 0; round < maxRound; round++) {
		/* 이벤트 상태 설정 */
		if (ev_gen_count >= targetEventGen) {
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE) {
				break;
			} else {
				Sleep(500);
				continue;
			}
		}

		/* 가상 이벤트 생성 */
		ev_no = ev_gen_count + NUM_EVENTS_PER_GEN * myAddr;
		ev_priority = targetEventGen - ev_gen_count - 1;
		evt_no_str = std::format("{:02}", ev_no);
		evt_name = std::string("evt_") + evt_no_str;
		pEv = new Event(ev_no, ev_priority, evt_name, ev_gen_addr);
		
		pEv->setEventName(evt_name);
		pEv->setEventGenAddr(myAddr);
		pEv->setEventHandlerAddr(-1);
		QueryPerformanceCounter(&t_gen);
		pEv->setEventGenTime(t_gen);
		pEv->setEventStatus(GENERATED);

		/* 환형큐가 가득 차면 잠시 대기 */
		while (pCirQ_Event->enqueue(*pEv) == NULL) {
			pThrdParam->pCS_main->lock();
			std::cout << "CirQ_Event is Full, waiting ..." << std::endl;
			pThrdParam->pCS_main->unlock();
			Sleep(1000);  
		}

		
		/* 락 해제 후 다시 이벤트 추가 */
		pParam->pCS_main->lock();
		std::cout << "Successfully inserted into CirQ_Event "
			<< *pEv << std::endl;
		pParam->pCS_main->unlock();
		
		pThrdParam->pCS_thrd_mon->lock();
		pThrdMon->eventGenerated[pThrdMon->totalEventGenerated] = *pEv;
		pThrdMon->numEventGenerated[myAddr]++;
		pThrdMon->totalEventGenerated++;
		pThrdParam->pCS_thrd_mon->unlock();
		ev_gen_count++;
		delete pEv;
		Sleep(100);
	}
}
