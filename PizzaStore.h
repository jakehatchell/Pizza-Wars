// Jake Hatchell, 10/22/2023

#ifndef PIZZASTORE_H	// header gaurds
#define PIZZASTORE_H		
#include "Date.h"	// Date class header file
#include <string>	// used to create functions that return strings

using namespace std;

class PizzaStore {
	private:
		int *storePtr;
		string storeName;
		int storeMaxPizzas;
		double storeProductionPerTick, storeSuccessRate;
	public:
		PizzaStore();	// default constructor
		PizzaStore(string name, int maxPizzas, double productionPerTick, double successRate);	// overloaded constructor
		~PizzaStore();		// destructor
		int tickUpdate();	// runs one tick of the simulation (every 30 min)
		bool consumeSlices(int slices);	// subtracts slices from both pizza stores (returns false if the order cannot be fullfilled)
		void showStatus();	// prints the pizza stacks that are currently out
		string getName();	// gets the name of this PizzaStore
		int getTotalSlicesLeft();	// gets the total number of PizzaSlices of this PizzaStore
		void resetArray();	// helper function that refills all pizzas in this Pizza store (called in the constructor and after each day)
};

#endif
