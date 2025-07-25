Dining Philosophers Solution


This repository contains a basic solution to the Dining Philosophers Problem, implemented as part of the 42 Philosophers project. The program simulates philosophers sitting at a table, thinking, eating, and sleeping, while avoiding deadlocks and starvation.

Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Usage](#usage)
- [Parameters](#parameters)
- [Compilation](#compilation)
- [Example](#example)
- [License](#license)

---

Overview


The Dining Philosophers Problem is a classic synchronization problem in computer science. It involves philosophers sitting at a table with forks between them. Each philosopher alternates between thinking, eating, and sleeping, but they must acquire forks to eat. The challenge is to ensure that no philosopher starves or causes a deadlock.

This solution uses multithreading to simulate the philosophers' behavior and ensures proper synchronization using mutexes.


---

Features

- Simulates the behavior of philosophers:
	- Thinking
	- Eating
	- Sleeping
- Prevents deadlocks and starvation.
- Configurable parameters for simulation.
- Lightweight and efficient implementation.

---

Usage

Parameters


The program philo accepts the following parameters:


1. number_of_philos: The number of philosophers (and forks).
2. time_to_die: Time (in milliseconds) a philosopher can go without eating before dying.
3. time_to_eat: Time (in milliseconds) a philosopher takes to eat.
4. time_to_sleep: Time (in milliseconds) a philosopher takes to sleep.
5. number_times_of_eating (optional): The number of times each philosopher must eat before the simulation ends. If not provided, the simulation runs indefinitely.

---

Compilation


To compile the program, use the provided Makefile. Simply run:


	make

This will compile all source files and create an executable named philo.

To clean up compiled files, run:


	make clean

To remove all compiled files and the executable, run:


	make fclean

To recompile the program from scratch, run:


	make re


---

Running the Program


After compiling, you can run the program using the following syntax:


	./philo number_of_philos time_to_die time_to_eat time_to_sleep [number_times_of_eating]

Example

	./philo 5 800 200 200 5

This command simulates 5 philosophers with the following parameters:


- time_to_die: 800 ms
- time_to_eat: 200 ms
- time_to_sleep: 200 ms
- number_times_of_eating: 5 (each philosopher eats 5 times before the simulation ends).

---

Example Output


The program will output logs showing the philosophers' actions:


	0 ms: Philosopher 1 is thinking
	10 ms: Philosopher 1 is eating
	210 ms: Philosopher 1 is sleeping
	220 ms: Philosopher 2 is thinking
	...
