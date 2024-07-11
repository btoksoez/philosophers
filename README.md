# Philosophers
The "Philosophers" project at 42 involves simulating the classic dining philosophers problem, where philosophers must alternately eat, think, and sleep without starving.

## Project Overview
The project simulates a scenario where one or more philosophers sit at a round table with a bowl of spaghetti in the middle. Each philosopher alternates between eating, thinking, and sleeping. To eat, a philosopher must pick up two forks, one on their right and one on their left. After eating, they put the forks back and sleep before thinking again. The simulation continues until a philosopher dies of starvation. The goal is to ensure that no philosopher starves by managing the allocation of forks and avoiding deadlocks and race conditions.

## Key Concepts
- **Mutexes**: A mutex "mutual exclusion", is a synchronization primitive used to prevent multiple threads from accessing a shared resource simultaneously. It ensures that only one thread can lock the mutex at a time, thereby preventing data races.
- **Threads**: A thread is the smallest unit of processing that can be performed in an OS. In this project, each philosopher is represented by a thread, allowing their actions (eating, thinking, sleeping) to occur concurrently.
- **Deadlocks**: A deadlock is a state where a set of threads are blocked because each thread is holding a resource and waiting for another resource held by another thread. In the context of this project, it refers to the situation where each philsopher is holding the fork to their left and thus cannot pick up any fork to their right and get stuck.
- **Data Races**: A data race occurs when two threads access the same variable concurrently, and at least one of the accesses is a write. This can lead to undefined behavior. Proper synchronization mechanisms, like mutexes, are needed to avoid this. 
- **Monitor Thread**: A monitor thread is an additional thread that continuously checks the status of other threads. In this project, the monitor thread runs an infinite loop to check if any philosopher has died and sets a dead flag accordingly.


## How to Run the Code
Compile the program using the provided Makefile:
```
make
./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
Run the program with the following arguments:
- number_of_philosophers: The number of philosophers and forks.
- time_to_die (in milliseconds): Time until a philosopher dies if they don't start eating.
- time_to_eat (in milliseconds): Time it takes for a philosopher to eat.
- time_to_sleep (in milliseconds): Time a philosopher spends sleeping.
- number_of_times_each_philosopher_must_eat (optional): The simulation stops if all philosophers have eaten this many times. If not specified, the simulation stops when a philosopher dies.

## Tricky Things
- **Monitor Thread**: Implementing a monitor thread that runs an infinite loop, checking if any philosopher has died and setting the dead flag.
- **Preventing Deadlocks**: Philosophers with even numbers take the right fork first, while those with odd numbers take the left fork first.
- **Inaccurate usleep Function**: The standard C library usleep function is inaccurate and sleeps for different amounts of time depending on the hardware. A custom ft_usleep function was created to address this issue.
