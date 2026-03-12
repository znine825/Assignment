#include <stdio.h>
const char* monthName[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
const char* weekDayName[7] = { "SUN", "MON", "TUE", "WED", "THR", "FRI", "SAT" };

bool isleapYear(int year) {
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
		return true;
	}
	else {
		return false;
	}
}

int getDaysFromJan01AD01(int year, int month, int day) {
	int all_day = 0;
	int leap_year = 0;
	int month_day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	all_day = (year - 1) * 365;
	all_day += ((year - 1) / 4) - ((year - 1) / 100) + ((year - 1) / 400);

	if (isleapYear(year) == 1) {
		month_day[1] = 29;
	}

	for (int i = 0; i < month - 1; i++) {
		all_day += month_day[i];
	}

	all_day += day;

	return all_day;
}

void printData(int year, int month, int day) {
	int all_days = getDaysFromJan01AD01(year, month, day);
	printf("date(%s %2d, %4d) (%s) %7d-th day from Jan 1, 1.\n", monthName[month - 1], day, year, weekDayName[all_days % 7], all_days);

}

int main(void) {
	int year, month, day;

	while (true) {

		printf("Input year month day (0 0 0 to quit) : ");
		scanf("%d %d %d", &year, &month, &day);

		if (year == 0 && month == 0 && day == 0) {
			break;
		}
		printData(year, month, day);
		
	}
	return 0;
}