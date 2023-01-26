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
