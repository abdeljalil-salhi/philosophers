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
