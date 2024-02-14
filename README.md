# Pizza-Wars
A simulation of the dining halls on Clemson's campus.

In both the Core and Schilletter dining halls, pizza is served every day. This project simulates the student consumption
and baking of pizzas in both dining halls. If a location fails to keep up and runs out of pizza, they lose the Pizza
War.

Results of each simulation are stored in a file named log.txt. If the file does not exist, it will be created.
If it does, simulation results will be appended to the file.

Rules:
- The simulation runs for 7 days, starting on a Sunday.
- Core is able to have 3 pizzas out for consumption at once, Schilletter has 6
- Core can produce 2 pizzas per tick, Schilleter can produce 1
- Pizzas can be "dropped" causing them to never reach the students 
  - Pizzas at Core have a 20% chance of being dropped, Schilletter pizzas have a 10% chance of being dropped
- Each location can expect students to eat between 5 and 20 slices per tick
- The simulation ends when either location runs out of pizza or the 7 days ends

Note: as this was an assignment, the MysteryMachine object and header files were provided in advance with the
implementation intentionally hidden from the students. As a result, there is no MysteryMachine.cpp file within this
repository.
