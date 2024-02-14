// Jake Hatchell, 10/22/2023

#ifndef PIZZAWARS_H	// header gaurds
#define PIZZAWARS_H

#include <string>	// used to create member functions that return string objects
#include "Date.h"	// Date header file (some functions return dates and other accept them as parameters)
#include "PizzaStore.h"	// PizzaStore header file (some functions accept PizzaStores as parameters)

using namespace std;

class PizzaWars {

	public:
		PizzaWars();	// default constructor
		static void runSimulation();	// driver for the entire simulation
	protected:
		static Date * allocateWeekOfDates(Date date);	// returns a pointer to a dynamically allocated array of Date objects, starting with the Date passed in the parameter
		static void runSeriesSimulation(Date *dates, int length);	// runs simulations for an entire 7 day period and calls other member functions to write the results to a file.
		static string runDaySimulation(Date *datePtr, PizzaStore*, PizzaStore*);	// runs the simulation for a single day. makes calls to PizzaStore member functions
		static void marchToSunday(Date* datePtr);		// increments the Date at the datePtr pointer until that day is a Sunday
		static void writeToFile(Date *datePtr, PizzaStore *winner);	// writes the result of each day's battle to log.txt

};

#endif
