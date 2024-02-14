// Jake Hatchell, 10/22/2023

#include "PizzaWars.h"	// PizzaWars header file
#include <string>	// used to create string objects
#include "Date.h"	// Date header file (functions are using them as return types and parameters)
#include <iostream>	// used for cout and cin statements
#include <fstream>	// used to open and write to the log.txt file
#include <unistd.h>	// used to run the usleep function
#include <iomanip>	// used to format output

using namespace std;

PizzaWars::PizzaWars() {}	// default constructor

void PizzaWars::runSimulation() {	// simulation driver
	int tempMonth, tempDay, tempYear;
	cout << "Welcome to Pizza Wars!" << endl;
	cout << "This program simulates an epic battle between Core and Schilletter and their ability to keep up with the demand for pizza!" << endl << endl;
	cout << "Please enter the date you'd like to start the simulation in MM DD YYYY format: ";
	cin >> tempMonth;
	cin >> tempDay;
	cin >> tempYear;
	Date userDate(tempMonth, tempDay, tempYear);	// temporary Date object to hold the date the user entered above
	Date *startingDatePtr = &userDate;		// pointer pointing to the temporary date above
	if (userDate.getDayOfWeek() != "Sunday") {	// if the day is not a sunday, skip to the nearest sunday
		cout << "That day is not a Sunday, so we're moving to the nearest future Sunday to start" << endl;
		PizzaWars::marchToSunday(startingDatePtr);
	}
	startingDatePtr = PizzaWars::allocateWeekOfDates(*startingDatePtr);	// allocates an array of dates starting with the temporary Date
	cout << "Starting on " << (*startingDatePtr).toString() << endl;
	PizzaWars::runSeriesSimulation(startingDatePtr, 7);	// rusn the simulationi
	delete[] startingDatePtr;	// release memory of Date array
}

Date * PizzaWars::allocateWeekOfDates(Date date) {	// dynamically allocates an array of Dates with a lenght of 7 starting with Date passed as a paramter
	Date *dateArrayPtr = new Date[7];
	Date *tempDateArrayPtr = dateArrayPtr - 1;
	for (int i = 0; i < 7; i++) {
		tempDateArrayPtr++;
		*tempDateArrayPtr = (date + i);
	}
	return dateArrayPtr;
}

void PizzaWars::runSeriesSimulation(Date *dates, int length) {		// week-long simulation driver (series of day simulations)
	srand(time(0));		// seeds the random number generators for the entire program
	PizzaStore core("Core", 3, 2, 0.9);	//creates the core and schilletter objects
	PizzaStore schilletter("Schilletter", 6, 1, 0.8);
	PizzaStore *store1 = &core;	// pointers to the core and schilletter objects
	PizzaStore *store2 = &schilletter;
	PizzaStore *nullPtr = NULL;	// nullPtr used to control the write to file function if there is a tie
	string result;
	for (int i = 0; i < length; i++) {
		result = PizzaWars::runDaySimulation(dates + i, store1, store2);
		if (result == core.getName()) {
			PizzaWars::writeToFile(dates + i, store1);
			cout << "\t\t";
			(*store1).showStatus();
			cout << "\t\t";
			(*store2).showStatus();
			cout << "Core wins!" << endl;
		}
		else if (result == schilletter.getName()) {
			PizzaWars::writeToFile(dates + i, store2);
			cout << "\t\t";
			(*store1).showStatus();
			cout << "\t\t";
			(*store2).showStatus();
			cout << "Schilletter wins!" << endl;
		}
		else {
			PizzaWars::writeToFile(dates + i, nullPtr);
			cout << "Tie!" << "\n\n" << endl;
		}
		core.resetArray();	// refills the pizzas
		schilletter.resetArray();
	}
}

string PizzaWars::runDaySimulation(Date *datePtr, PizzaStore *store1, PizzaStore *store2) {	// runs the simulation for 1 day
	cout << "\n\nRunning simulation for " << (*datePtr).getDayOfWeek() << " " << (*datePtr).toString() << "\n" << endl;
	int timeCounter = 21;	// tells the loop how many times to iterate based on the open and closing times during week days and weekends. 
	int tempSlicesAte1 = 0, tempSlicesAte2 = 0;
	string timesOfDay[] {"11:00", "11:30", "12:00", "12:30", "1:00", "1:30", "2:00", "2:30", "3:00", "3:30", "4:00", "4:30", "5:00", "5:30", "6:00", "6:30", "7:00", "7:30", "8:00", "8:30", "9:00"};
	if ((*datePtr).getDayOfWeek() == "Saturday" || (*datePtr).getDayOfWeek() == "Sunday")	// shortens operating hours if the day is a weekend
		timeCounter = 19;
	for (int i = 0; i < timeCounter; i++) {		// runs a single simulation for each time of the day
		cout << "\n" << timesOfDay[i] << endl;
		tempSlicesAte1 = (rand() % (16)) + 5;
		usleep(50000);	// sleeps between each tick
		tempSlicesAte2 = (rand() % (16)) + 5;
		cout << tempSlicesAte1 << " slice(s) are consumed at " << (*store1).getName() << endl;
		cout << tempSlicesAte2 << " slice(s) are consumed at " << (*store2).getName() << endl;
		if (!((*store1).consumeSlices(tempSlicesAte1)))
			return (*store2).getName();	// returns the name of the other store if this store fails to meet the demand
		if (!((*store2).consumeSlices(tempSlicesAte2)))
			return (*store1).getName();
		cout << "\t\t";
		(*store1).showStatus();
		cout << "\t\t";
		(*store2).showStatus();
		cout << (*store1).tickUpdate() << " pizza(s) were added at " << (*store1).getName() << endl;	// bakes and adds pizzas for both stores
		cout << (*store2).tickUpdate() << " pizza(s) were added at " << (*store2).getName() << endl;
		cout << "\t\t";
		(*store1).showStatus();
		cout << "\t\t";
		(*store2).showStatus();
	}
	return "\0";	// returns a null string of neither store wins
}

void PizzaWars::marchToSunday(Date* datePtr) {		// incriments this date until the day is a sunday
	while ((*datePtr).getDayOfWeek() != "Sunday")
		(*datePtr)++;
}

void PizzaWars::writeToFile(Date *datePtr, PizzaStore *winner) {	// writes the result of each day's simulation to log.txt file
	ofstream outputFile("log.txt", ios::app);	// opens the file in append mode
	if (winner == NULL) {	// if the function recieves a null pointer, the result is a tie.
		outputFile << setw(10) << left << (*datePtr).getDayOfWeek();
		outputFile << setw(10) << left << (*datePtr).toString(); 
		outputFile << "Tie!" << endl;
	}
	else {
	outputFile << setw(10) << left << (*datePtr).getDayOfWeek();
       	outputFile << setw(10) << left << (*datePtr).toString();
       	outputFile << (*winner).getName() << " won with " << (*winner).getTotalSlicesLeft() << " slices left!"<< endl;
	}
	outputFile.close();
}
