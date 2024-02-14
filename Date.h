// Jake Hatchell, 10/22/2023

#ifndef DATE_H	// header gaurds
#define DATE_H

#include <string>

using namespace std;

class Date {
	private:
		int month, day, year;
	public:
		Date();	// default constructor
		Date(int month, int day, int year);	// overloaded constructor

		int getMonth();	// returns this date's month
		int getDay();	// returns this date's day
		int getYear();	// returns this date's year

		void setMonth(int month);	// sets this day's month
		void setDay(int day);		// sets this date's day
		void setYear(int year);		// sets this date's year

		// Overload Operators
		Date operator+ (int days);	// addition operator
		Date operator- (int days);	// subtraction operator
		Date operator++ (void);		//prefix incrementation
		Date operator++ (int);		//postfix incrementation
		Date operator-- (void);		//prefix decrementation
		Date operator-- (int);	 	//postfix decrementation
		
		string getDayOfWeek();		//returns the day of the week of this Date
		string toString();		// converts this Date into a string

};
#endif
