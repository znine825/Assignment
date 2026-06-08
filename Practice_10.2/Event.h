/*
Event.h
Date : 2026-05-22
Author : Lee Jong Kwang
- 가상 이벤트 구현을 위한 해더 파일
*/


#ifndef EVENT_H
#define EVENT_H
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <iomanip>

/* 이벤트의 상태 열거 */
enum EventStatus {
	GENERATED, ENQUEUED, PROCESSED,
	UNDEFINED
};

#define MAX_EVENT_PRIORITY 100
#define NUM_EVENT_GENERATORS 10

/* 클래스 이벤트 */
class Event {
	/* 출력을 위한 <<연산자 오버로딩 */
	friend std::ostream& operator<<(std::ostream& fout, const Event& e);

public:
	/* 기본 생성자 */
	Event();
	/* 메게변수 생성자 */
	Event(int event_id, int event_pri, std::string nm, int genAddr);
	/* 이벤트 변호 설정 기능 */
	void setEventNo(int evtNo) { event_no = evtNo; }
	/* 이벤트 우선순위 설정 기능 */
	void setEventPri(int pri) { event_pri = pri; }
	/* 이벤트 이름 설정 기능 */
	void setEventName(std::string nm) { event_name = nm; }
	/* 이벤트 Handler주소 설정 기능 */
	void setEventHandlerAddr(int evtHndlerAddr) { event_handler_addr = evtHndlerAddr; }
	/* 이벤트 생성 주소 설정 기능 */
	void setEventGenAddr(int genAddr) { event_gen_addr = genAddr; }
	/* 이벤트 상태 설정 기능 */
	void setEventStatus(EventStatus evtStatus) { eventStatus = evtStatus; }
	/* 이벤트 생성 시간 설정 기능 */
	void setEventGenTime(LARGE_INTEGER t_gen) { t_event_gen = t_gen; }
	/* 이벤트 실행 시간 설정 기능 */
	void setEventProcTime(LARGE_INTEGER t_proc) { t_event_proc = t_proc; }
	/* 생성 시간 반환 기능 */
	LARGE_INTEGER getEventGenTime() { return t_event_gen; }
	/* 실행 시간 반환 기능 */
	LARGE_INTEGER getEventProcTime() { return t_event_proc; }
	/* 실행시 걸린 시간 설정 기능 */
	void setEventElaspsedTime(double t_elapsed_ms) { t_elapsed_time_ms = t_elapsed_ms; }
	/* 실행시 걸린 시간 반환 기능 */
	double getEventElapsedTime() { return t_elapsed_time_ms; }
	/* 이벤트 우선순위 반환 기능 */
	int getEventPri() { return event_pri; }
	/* 이벤트 번호 반환 기능 */
	int getEventNo() { return event_no; }
	/* 비교를 위한 연산자 오버로딩 */
	bool operator>(Event& e) { return (event_pri > e.event_pri); }
	bool operator<(Event& e) { return (event_pri < e.event_pri); }

private:
	int event_no;
	int event_pri;
	std::string event_name; 
	int event_gen_addr;
	int event_handler_addr;
	LARGE_INTEGER t_event_gen;
	LARGE_INTEGER t_event_proc;
	double t_elapsed_time_ms;
	EventStatus eventStatus;
};

/* 랜덤 이벤트 생성 기능 */
Event* genRandEvent(int evt_no);
/* 이벤트 한번에 출력하는 기능 */
std::ostream& printEvents(std::ostream& fout, Event* events, int size, int per_line);
#endif