/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 04:37:33 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/20 13:24:58 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/includes/philosophers.h"
#include <time.h>

long long int	test = 0;
int				lock = 0;
pthread_mutex_t	mutex;

void	*routine2(void *arg)
{
	(void) arg;
	for (long long int i = 0; i < 1000000000000000; i++)
	{
		while (lock)
			;// wait until the lock is 0
		lock = 1;
		test++;
		lock = 0;
	}
	return (0);
}

void	*routine(void *arg)
{
	int	*ret;
	int	index;
	
	index = *(int *)arg;
	for (long long int i = 0; i < 10000000; i++)
		pthread_mutex_lock(&mutex), test++, pthread_mutex_unlock(&mutex);
	ret = (int *) malloc(sizeof(int));
	*ret = (rand() % 6) + 1;
	if (pthread_mutex_trylock(&mutex) == 0)
		printf("pthread %d got lock\n", index), sleep(1), pthread_mutex_unlock(&mutex);
	else
		printf("pthread %d didn't get lock\n", index);
	free(arg);
	return (ret);
}

int	main(void)
{
	pthread_t	threads[4];
	int			*res[4];

	srand(time(0));
	pthread_mutex_init(&mutex, 0);
	for (int i = 0; i < 4; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(threads + i, 0, &routine, a))
			return (1);
		printf("thread %d has started\n", i);
	}
	for (int i = 0; i < 4; i++)
	{
		if (pthread_join(threads[i], (void **) &res[i]))
			return (2);
		printf("thread %d has finished\n", i);
	}
	for (int i = 0; i < 4; i++)
		printf("thread %d roll dice result: %d\n", i, *res[i]), free(res[i]);
	pthread_mutex_destroy(&mutex);
	printf("%lld\n", test);
	return (0);
}