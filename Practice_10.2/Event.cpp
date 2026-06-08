/*
Event.cpp
Date : 2026-05-22
Author : Lee Jong Kwang
- 가상 이벤트 구현을 위한 기능 파일
*/

#include <iostream>
#include <iomanip>
#include "Event.h"

/* 기본 생성자 */
Event::Event() {
	this->event_no = 0;
	this->event_pri = 0;
	this->event_name = "";
	this->event_gen_addr = 0;
	this->event_handler_addr = 0;
	this->t_event_gen.QuadPart = 0;
	this->t_event_proc.QuadPart = 0;
	this->t_elapsed_time_ms = 0.0;
	this->eventStatus = UNDEFINED;
}

/* 메게변수 생성자 */
Event::Event(int evt_no, int evt_pri, std::string nm, int evtGenAddr) {
	this->event_no = evt_no;
	this->event_pri = evt_pri;
	this->event_name = nm;
	this->event_gen_addr = evtGenAddr;
	this->event_handler_addr = -1;
	this->t_event_gen.QuadPart = 0;
	this->t_event_proc.QuadPart = 0;
	this->t_elapsed_time_ms = 0.0;
	this->eventStatus = GENERATED;
}

/* 랜덤 이벤트 생성 기능 */
Event* genRandEvent(int evt_no) {
	Event* pEv;
	int evt_prio;
	int evt_generator_id;
	std::string evt_nm;
	evt_nm = std::string("evt_") + std::to_string(evt_no);
	evt_prio = rand() % MAX_EVENT_PRIORITY;
	evt_generator_id = rand() % NUM_EVENT_GENERATORS;
	pEv = new Event(evt_no, evt_prio, evt_nm, evt_generator_id);
	return pEv;
}

/* 출력을 위한 <<연산자 오버로딩 */
std::ostream& operator<<(std::ostream& fout, const Event& evt) {
	fout << "Ev(no:" << std::setw(3) << evt.event_no;
	fout << ", pri:" << std::setw(3) << evt.event_pri;
	fout << ", " << evt.event_name;
	fout << ")";
	return fout;
}

/* 이벤트 한번에 출력하는 기능 */
std::ostream& printEvents(std::ostream& fout, Event* events,
	int size, int per_line) {
	int count = 0;
	Event* pEv = events;
	if (events == NULL)
		return fout;
	while (count < size) {
		for (int i = 0; (i < per_line && count < size); i++) {
			fout << *pEv++ << " ";
			count++;
		}
		fout << std::endl;
	} return fout;
}