#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <string>
#include "Date.h"

int main(void) {
	Date AD010101(1, 1, 1);
	int year, month, day, dayToChristmas;
	time_t currentTime;

	struct tm* time_and_date;

	time(&currentTime);
	time_and_date = localtime(&currentTime);
	year = time_and_date->tm_year + 1900;
	month = time_and_date->tm_mon + 1;
	day = time_and_date->tm_mday;

	Date newYearDay(year, 1, 1), today(year, month, day), christmas(year, 12, 25);

	cout << "AD JAN 1, 1 is ";
	AD010101.outputDate();

	cout << "Today is ";
	today.outputDate();

	cout << "New year's day of this year was ";
	newYearDay.outputDate();

	cout << "Chrismas of this year was ";
	christmas.outputDate();
	cout << endl;

	if (today.getMonth() == christmas.getMonth() && today.getDay() == christmas.getDay()) {
		cout << "Today is Christmas! Happy Christmas to you all!! \n";
	}
	else {
		cout << "Sorry, today is not CHristmas..\n";
		dayToChristmas = christmas.getElapsedDay() - today.getElapsedDay();
		cout << "You must wait " << dayToChristmas << " day(s) to Christmas!";
	}

	cout << endl;
	return 0;
}