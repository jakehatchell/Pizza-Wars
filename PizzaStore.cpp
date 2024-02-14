// Jake Hatchell, 10/22/2023

#include "PizzaStore.h"		// PizzaStore header file
#include "Date.h"		// Date header file

#include <iostream>	// used to print to the screen and take input
#include <string>	// used to create and return string objects
#include <unistd.h>	// used to sleep the program
#include <cstdlib>	// used to get the srand() and rand() functions working
#include <ctime>	// used to get the current calender time (seeding for the srand() function)

using namespace std;

PizzaStore::PizzaStore() {}	// default constructor

PizzaStore::PizzaStore(string name, int maxPizzas, double productionPerTick, double successRate) {	// overloaded constructor
	storeName = name;
	storeMaxPizzas = maxPizzas;
	storeProductionPerTick = productionPerTick;
	storeSuccessRate = successRate;
	storePtr = new int[maxPizzas];	// points to a dynamically allocated array that hold each pizza in this store
	(*this).resetArray();	// fills every slot with a full pizza
}

PizzaStore::~PizzaStore() {	// destructor to release dynamically allocated memory
	delete[] storePtr;
}

void PizzaStore::resetArray() {		// refills all pizzas in this store
	for (int i = 0; i < (*this).storeMaxPizzas; i++) {
		int *tempPointer = ((*this).storePtr) + i;
		*tempPointer = 8;
	}
}

int PizzaStore::tickUpdate() {		// bakes and adds pizzas to this shop, accounting for the maximum production and their chance of failure
	int pizzasRemaining = storeProductionPerTick;
	int temporary = 0;
	int counter = 0;
	for (int i = 0; i < (*this).storeMaxPizzas; i++) {
		if (*((*this).storePtr + i) == 0 && pizzasRemaining > 0) {

			temporary = rand() % 100;	// calculates whether or not the pizza has been dropped.
			if (!(temporary >= (storeSuccessRate * 100))) {
				*((*this).storePtr + i) = 8;
				pizzasRemaining--;
				counter++;
			}
			else 
				pizzasRemaining--;
		}
		else
			return counter;
	}
	return -1;
}

bool PizzaStore::consumeSlices(int slices) {		//subtracts (slices) number of slices from the current pizza stack, returning false if the order cannot be met
	for (int i = 0; i < (*this).storeMaxPizzas; i++) {
		while (*(((*this).storePtr + i)) > 0 && slices > 0) {
			*(((*this).storePtr + i)) -= 1;
			slices--;
		}
	}
	if (slices > 0)
		return false;
	return true;
}

void PizzaStore::showStatus() {		// prints out the current pizza stack of this store
	cout << storeName << ": ";	
	for (int i = 0; i < (*this).storeMaxPizzas; i++)
		cout << *(((*this).storePtr) + i) << " ";
	cout << endl;
}

string PizzaStore::getName() {	// returns the name of this store
	return storeName;
}

int PizzaStore::getTotalSlicesLeft() {	// returns the total number of slices in the current pizza stack of this store
	int total = 0;
	for (int i = 0; i < (*this).storeMaxPizzas; i++)
		total += *((*this).storePtr + i);
	return total;
}
