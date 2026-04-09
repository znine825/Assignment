#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Date.h"


enum WEEKDAY { SUN, MON, TUE, WED, THU, FRI, SAT };

Date::Date() {
	year = 0;
	month = 0;
	day = 0;
}

Date::Date(int y, int m, int d) {
	setDate(y, m, d);
}

void Date::inputDate() {
	int y, m, d;

	cout << "Enter date in year month day : ";
	cin >> y >> m >> d;
	if (isValidDate(y, m, d)) {
		setDate(y, m, d);
	}
	else {
		cout << "legal date value! Programe aborted.\n";
		exit(1);
	}
}
void Date::outputDate() {
	const char* weekDayName[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
	const char* monthName[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	int weekDay = getWeekDay();
	cout << "today is, " << monthName[month - 1] << " " << day << ", " << year << " (" << weekDayName[weekDay] << ").\n";
}

void Date::setDate(int y, int m, int d) {
	year = y;
	if ((m < 1) || (m > 12)) {
		cout << "legal month value! Programe aborted.\n";
		exit(1);
	}
	else {
		month = m;
	}

	if ((d < 1) || (d > 31)) {
		cout << "legal day value! Programe aborted.\n";
		exit(1);
	}
	else {
		day = d;
	}
}

/* 윤년 확인 기능 */
bool Date::isLeapYear(int y) {
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
		return true;
	}
	else {
		return false;
	}
}

/* 올해 지난 일 수 계산 기능*/
int Date::getYearDay() {
	int days_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int days = 0;

	if (isLeapYear(year)) {
		days_month[1] = 29;
	}

	for (int i = 0; i < month - 1; i++) {
		days += days_month[i];
	}
	return days + day;
}

/* 요일 계산 기능*/
int Date::getWeekDay() {
	int days = getElapsedDay();
	return days % 7;
}

int Date::getElapsedDay() {
	int days = 0;

	days = (year - 1) * 365;
	days += ((year - 1) / 4) - ((year - 1) / 100) + ((year - 1) / 400);

	return days + getYearDay();
}

/* 알맞은 Date인지 확인하는 기능 */
bool Date::isValidDate(int y, int m, int d) {
	int days_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (y <= 0) {
		cout << "legal year value!\n";
		return 0;
	}

	if (isLeapYear(y)) days_month[1] = 29;

	if ((m <= 0) || (m > 12)) {
		cout << "legal month value!\n";
		return 0;
	}

	if ((0 >= d) || d > days_month[m - 1]) {
		cout << "legal day value!\n";
		return 0;
	}

	return 1;
}

void Date::testOutPutdays() {
	int test = getElapsedDay();
	cout << test << endl;
}