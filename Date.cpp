// Jake Hatchell, 10/22/2023

#include <iostream>	// included to allow for input and output to the terminal
#include <string>	// included to created and modify string objects
#include "Date.h"	// Date header file to use member functions of the date class
#include "MysteryMachine.h"	// Mystery machine header file which is used to get the current day of the week based on the date inputed

using namespace std;

Date::Date() {		// default constructor which sets the month to Jan 1st, 2000
	month = 1;
	day = 1;
	year = 2000;
}

Date::Date(int month, int day, int year) {	// overloaded constructor used to build custom dates
	this -> month = month;
	this -> day = day;
	this -> year = year;
}

// getter functions

int Date::getMonth() {	// returns the month of this date as an interger
	return month;
}

int Date::getDay() {	// returns the day of this date as an integer
	return day;
}

int Date::getYear() {	// returns the year of this date as an integer
	return year;
}

// setter functions

void Date::setMonth(int month) {	// sets this date's month to the parameter in the function header. If the date is greater than 12, it is deafaulted to 12
	if (month > 12)
		(*this).setMonth(12);
	else
		this -> month = month;
}

void Date::setDay(int day) {	// sets this date's day to the parameter in the function header. If the day is greater than the number of valid days within a given month, it is defeaulted to the last day in the current month
	int daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (day > daysPerMonth[month - 1])
		(*this).setDay(daysPerMonth[month - 1]);
	else
		this -> day = day;
}
void Date::setYear(int year) {		// sets this date's year to the parameter in the function header
	this -> year = year;
}

// overloaded operators

Date Date::operator+ (int days) {	// allows for addition of a Date and and integer. Will add (int) number of days to this date
	// adds the new days to the current number of days
	int daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int newDays = (day + days), newYears = year, newMonths = month;
	// checks to see if the number of days has gone out of bounds and corrects the number of months
	while (newDays > daysPerMonth[newMonths - 1]) {
		newDays -= daysPerMonth[newMonths - 1];
		++newMonths;
		if (newMonths > 12) {		// checks if the number of months has gone out of bounds and corrects the number of years
			newMonths = 1;
			newYears++;
		}
	}
	
	int tempNewMonths = newMonths;
	// checks if the number of days is lower than 0; if so, the months and years are adjested accordingly
	while (newDays <= 0) {
		if (tempNewMonths == 1) {
			tempNewMonths = 13;
			newYears--;
		}
		newDays += daysPerMonth[tempNewMonths - 2];
		--tempNewMonths;
	}
	// creates a new Date object to return the new Date
	Date returnDate(tempNewMonths, newDays, newYears);
	return returnDate;
}

Date Date::operator++ (int) {		// allows for postfix incrementation of a Date. returns Date prior to incrimentation
	Date tempDate((*this).month, (*this).day, (*this).year);
	(*this) = (*this) + 1;
	return tempDate;
}

Date Date::operator++ (void) {		// allows for prefix incrementation of a Date. increments this Date then returns the value
	(*this) = (*this) + 1;
	return (*this);
}


Date Date::operator- (int days) {	// allows for subtraction of a Date and an integer. Makes use of the addition overloaded operator by adding a negeative number of days to this date
	return ((*this) + (0 - days));
}

Date Date::operator-- (int) {		// allows for prefix decrementation of a Date. returns Date prior to decrementation
	Date tempDate((*this).month, (*this).day, (*this).year);
	(*this) = (*this) - 1;
	return tempDate;
}

Date Date::operator-- (void) {		// allows for postfix decrementation of a Date. returns Date after decremenation
	(*this) = (*this) - 1;
	return (*this);
}

string Date::toString() {		// converts this Date to a formatted and printable string
	return to_string(month) + "/" + to_string(day) + "/" + to_string(year);
}

string Date::getDayOfWeek() { 		// gets this Date's current day of the week
	return MysteryMachine::getDayOfWeek(*this);
}
