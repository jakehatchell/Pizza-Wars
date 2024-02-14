compile:
	g++ -c driver.cpp Date.cpp PizzaWars.cpp PizzaStore.cpp -Wall
	g++ -o battle.out driver.o Date.o MysteryMachine.o PizzaWars.o PizzaStore.o

run:
	./battle.out

clean:
	rm *.out
