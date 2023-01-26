# Philosophers - 42 project

<p align="center">
    <a href="https://projects.intra.42.fr/projects/42cursus-philosophers/projects_users/2935014" alt="absalhi's philosophers">
        <img src="https://user-images.githubusercontent.com/65598953/214819826-47467fd2-209e-43e1-a48a-f590ef26ef3c.png" alt="philosophers" />
    </a>
    <br />
    <a href="https://projects.intra.42.fr/projects/42cursus-philosophers/projects_users/2935014">
        <img src="https://badge42.vercel.app/api/v2/cl9iseqxd00640gl9mg4g0mxp/project/2935014" alt="absalhi's 42 philosophers Score" />
    </a>
</p>

---

<p align="center">
	<img src="https://user-images.githubusercontent.com/65598953/214820503-5997179d-152a-4aa1-91d3-7fd1f9569f93.png" width="500"/>
</p>

## Usage

```bash
$> make
$> ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

## Description

Eat, Sleep, Spaghetti, repeat. This project is about learning how threads work by precisely timing a group of philosophers on when to pick up forks and eat spaghetti without dying from hunger.

The Philosopher's Dining Problem is a classic problem in computer science that illustrates the concept of deadlock and synchronization. The problem describes a scenario where a group of philosophers are seated around a round table and are each trying to eat their dinner. However, in order to eat, they must first pick up the chopsticks that are located between them and their neighbors.

In the C programming language, this problem can be implemented using threads and synchronization mechanisms such as semaphores or mutexes. Here's an example of how to implement the Philosopher's Dining Problem using semaphores:

1. Declare an array of semaphores, one for each chopstick.
2. Create a function for each philosopher thread that will run concurrently. Inside the function, the philosopher will first wait on the semaphore for the chopstick to their left, then wait on the semaphore for the chopstick to their right. Once both chopsticks are acquired, the philosopher can eat for a random amount of time.
3. Initialize each semaphore with a value of 1 to represent that the chopstick is available.
4. Create the philosopher threads and start them.
5. Wait for all threads to complete.
6. Release resources and exit the program.

Here is a sample code snippet for implementing the philosopher's dining problem using threads and mutexes (minimal example):

```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t	chopsticks[NUM_PHILOSOPHERS];

void *philosopher(void *num) {
	int	id;

	id = *(int*)num;
    while(1)
	{
        printf("Philosopher %d is thinking\n", id);
        sleep(rand() % 3);
        printf("Philosopher %d is hungry\n", id);
        pthread_mutex_lock(&chopsticks[id]);
        pthread_mutex_lock(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d is eating\n", id);
		sleep(rand() % 3);
		pthread_mutex_unlock(&chopsticks[id]);
		pthread_mutex_unlock(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);
	}
}

int main(void)
{
	int			i;
	int			nums[NUM_PHILOSOPHERS];
	pthread_t	philosophers[NUM_PHILOSOPHERS];

	for(i = 0; i < NUM_PHILOSOPHERS; i++)
		pthread_mutex_init(&chopsticks[i], NULL);
	for(i = 0; i < NUM_PHILOSOPHERS; i++)
	{
		nums[i] = i;
		pthread_create(&philosophers[i], NULL, philosopher, &nums[i]);
	}
	for(i = 0; i < NUM_PHILOSOPHERS; i++)
		pthread_join(philosophers[i], NULL);
	for(i = 0; i < NUM_PHILOSOPHERS; i++)
		pthread_mutex_destroy(&chopsticks[i]);
	return (0);
}
```

We used mutexes to implement the dining philosophers problem. Mutexes are a synchronization mechanism that allows us to lock and unlock resources. In the above example, we use a mutex to lock a chopstick before a philosopher can pick it up. If the chopstick is already locked, the philosopher will wait until the chopstick is unlocked before picking it up. Once the philosopher is done eating, they will unlock the chopstick so that another philosopher can pick it up.

Additionally, the `pthread_mutex_init()`, `pthread_create()`, `pthread_join()` and `pthread_mutex_destroy()` functions are used to initialize, create, wait for completion, and destroy the mutexes, respectively.

It's worth noting that the problem of deadlock can still occur if the philosophers are not implemented correctly. To avoid deadlock, philosophers must always acquire chopsticks in the same order _(e.g. left, then right)_ and handle errors correctly.

Also, in this example, the philosophers are eating infinitely, you may want to add a condition to the while loop to make sure it stops after a certain number of iterations.

As always, it's important to test this program with different inputs and different scenarios to ensure that it is working correctly and that it is not prone to deadlock or starvation.

Here is the same implementation but using forks and semaphores this time _(this is for the bonus part, it ain't that hard; give it a shot !!)_:

```c
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_PHILOSOPHERS 5

sem_t	forks[NUM_PHILOSOPHERS];

void philosopher(int id) {
    while(1)
	{
        printf("Philosopher %d is thinking\n", id);
        sleep(rand() % 3);
        printf("Philosopher %d is hungry\n", id);
        sem_wait(&forks[id]);
        sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d is eating\n", id);
        sleep(rand() % 3);
        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % NUM_PHILOSOPHERS]);
    }
}

int main(void)
{
    int		i;
    pid_t	pid;

    for(i = 0; i < NUM_PHILOSOPHERS; i++)
        sem_init(&forks[i], 0, 1);
    for(i = 0; i < NUM_PHILOSOPHERS; i++)
	{
        pid = fork();
        if(pid == 0)
		{
            philosopher(i);
            return (0);
        }
    }
    for(i = 0; i < NUM_PHILOSOPHERS; i++)
        wait(NULL);
    for(i = 0; i < NUM_PHILOSOPHERS; i++)
		sem_destroy(&forks[i]);
	return (0);
}
```

In this example, the `sem_init()`, `sem_wait()`, `sem_post()`, and `sem_destroy()` functions are used to initialize, acquire, release, and destroy the semaphores, respectively. The `fork()` function is used to create child processes for each philosopher, and the `wait()` function is used to wait for all child processes to complete before exiting the program.

Just as in the mutex implementation, philosophers must always acquire forks in the same order _(e.g. left, then right)_ and handle errors correctly to avoid deadlock.

It is important to test the program with different inputs and different scenarios to ensure that it is working correctly and that it is not prone to deadlock or starvation.

Also, in this example, the philosophers are eating infinitely, you may want to add a condition to the while loop to make sure it stops after a certain number of iterations.
