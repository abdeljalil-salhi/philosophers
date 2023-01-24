/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 00:34:27 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/24 03:17:12 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
	 This is the routine function for each philosopher where he creates a thread
	 	to check if any of the philosophers is dead, and goes in the routine..
*/
void	ft_routine(t_philo *g, t_philos *philo)
{
	unsigned long	_time;
	pthread_t		check;

	_time = ft_get_time(NULL);
	if (!_time)
		exit(1);
	philo->next_meal = _time + g->routine.time_to_die;
	if (pthread_create(&check, NULL, &ft_routine_if_valid, philo))
		exit(1);
	if (g->exit_message)
		exit(1);
	if (pthread_detach(check))
		exit(1);
	while (1)
	{
		if (ft_take_forks(g, philo))
			exit(1);
		if (ft_eat(g, philo))
			exit(1);
		if (ft_sleep(g, philo))
			exit(1);
		if (ft_print_action(g, philo, THINKING))
			exit(1);
	}
	exit(0);
}

/*
	 This is the function that locks the waits the semaphore for
	 	each philosopher to take two forks during its turn.
*/
int	ft_take_forks(t_philo *g, t_philos *philo)
{
	if (sem_wait(philo->philo->forks))
		return (ft_error(g, ERR_FORKS_SEMAPH_WAIT));
	if (ft_print_action(g, philo, TOOK_FORK))
		return (1);
	if (sem_wait(philo->philo->forks))
		return (ft_error(g, ERR_FORKS_SEMAPH_WAIT));
	if (ft_print_action(g, philo, TOOK_FORK))
		return (1);
	return (0);
}

/*
	 This is the function where each philosopher eats, increasing the
	 	value of the `meals` semaphore, then put down the forks.
*/
int	ft_eat(t_philo *g, t_philos *philo)
{
	if (ft_print_action(g, philo, EATING))
		return (1);
	if (sem_post(g->meals))
		return (ft_error(g, ERR_MEALS_SEMAPH_POST));
	philo->ate_at = ft_get_time(NULL);
	if (!philo->ate_at)
		return (ft_error(g, ERR_TIME));
	philo->next_meal = philo->ate_at + (unsigned long) g->routine.time_to_die;
	if (ft_usleep(g, g->routine.time_to_eat) == -1)
		return (1);
	if (sem_post(philo->philo->forks))
		return (ft_error(g, ERR_FORKS_SEMAPH_POST));
	if (sem_post(philo->philo->forks))
		return (ft_error(g, ERR_FORKS_SEMAPH_POST));
	return (0);
}

/*
	 This is the function where each philosopher sleeps.
*/
int	ft_sleep(t_philo *g, t_philos *philo)
{
	if (usleep(10) == -1)
		return (ft_error(g, ERR_SLEEP));
	if (ft_print_action(g, philo, SLEEPING))
		return (1);
	if (ft_usleep(g, g->routine.time_to_sleep) == -1)
		return (1);
	return (0);
}

/*
	 This function checks if a philosopher is dead
	 	and waits the `check` semaphore in the main thread.
*/
int	ft_routine_check(t_philo *g, t_philos *philo, unsigned long *_time)
{
	if (sem_wait(g->check))
		return (ft_error(g, ERR_CHECK_SEMAPH_WAIT));
	*(_time) = ft_get_time(NULL);
	if (!*(_time))
		return (ft_error(g, ERR_TIME));
	if (philo->next_meal < *(_time))
	{
		g->is_done = 1;
		if (ft_print_action(g, philo, DEAD))
			return (1);
		if (sem_post(g->wait))
			return (ft_error(g, ERR_WAIT_SEMAPH_POST));
		return (2);
	}
	if (sem_post(g->check))
		return (ft_error(g, ERR_CHECK_SEMAPH_POST));
	if (sem_wait(g->check))
		return (ft_error(g, ERR_CHECK_SEMAPH_WAIT));
	return (0);
}
