#pragma once
#include <iostream>
#include <cstdlib>

using namespace std;

class Date {
public:
	Date();
	Date(int y, int m, int d);

	void testOutPutdays();

	void inputDate();
	void outputDate();
	void setDate(int y, int m, int d);
	void setMonth(int m);

	int getYear() { return year; }
	int getMonth() { return month; }
	int getDay() { return day; }
	int getYearDay();
	int getWeekDay();
	int getElapsedDay();

private:
	bool isLeapYear(int y);
	bool isValidDate(int y, int m, int d);
	int year, month, day;
};