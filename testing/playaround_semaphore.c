/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playaround_semaphore.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:23:13 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/26 12:17:29 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <limits.h>
#include <sys/time.h>
#include <semaphore.h>

#define THREADS 4

sem_t	*semaphore;

void	*routine(void *args)
{
	(void) args;
	sem_wait(semaphore);
	sleep(1);
	printf("Hello from thread\n");
	sem_post(semaphore);
	return (NULL);
}

int	main(void)
{
	pthread_t	th[THREADS];

	// if there is a semaphore create it, otherwise just use it
	semaphore = sem_open("wait", O_CREAT | O_EXCL, 0644, 1);
	for (int i = 0; i < THREADS; i++)
		if (pthread_create(&th[i], NULL, &routine, NULL))
			perror("create_thread");
	for (int i = 0; i < THREADS; i++)
		if (pthread_join(th[i], NULL))
			perror("join_thread");
	sem_unlink("wait");
	sem_close(semaphore);
	return (0);
}
