/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:14:30 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/24 02:57:52 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
	 The ft_init_struct() function initializes the `t_philo *g` struct.
*/
int	ft_init_struct(t_philo *g)
{
	size_t	i;

	g->philos = (t_philos *) ft_calloc(g->n_philos, sizeof(t_philos));
	if (!g->philos)
		return (ft_error(g, ERR_PHILO_MALLOC));
	g->allocated.philos = 1;
	g->start = ft_get_time(NULL);
	if (!g->start)
		return (ft_error(g, ERR_TIME));
	if (ft_init_mutexes(g))
		return (1);
	i = -1;
	while (++i < g->n_philos)
		if (ft_init_philo(g, i))
			return (1);
	return (0);
}

/*
	 The ft_init_mutexes() function allocates the required area for
	 	the mutexes and initializes them.
*/
int	ft_init_mutexes(t_philo *g)
{
	g->print = (pthread_mutex_t *) ft_calloc(1, sizeof(pthread_mutex_t));
	if (!g->print)
		return (ft_error(g, ERR_PRINT_MUTEX_MALLOC));
	g->allocated.mutex_print = 1;
	if (pthread_mutex_init(g->print, NULL))
		return (ft_error(g, ERR_PRINT_MUTEX_INIT));
	g->wait = (pthread_mutex_t *) ft_calloc(1, sizeof(pthread_mutex_t));
	if (!g->wait)
		return (ft_error(g, ERR_WAIT_MUTEX_MALLOC));
	g->allocated.mutex_wait = 1;
	if (pthread_mutex_init(g->wait, NULL))
		return (ft_error(g, ERR_WAIT_MUTEX_INIT));
	if (ft_init_mutex_locks(g))
		return (1);
	g->forks = (pthread_mutex_t *)
		ft_calloc(g->n_philos, sizeof(pthread_mutex_t));
	if (!g->forks)
		return (ft_error(g, ERR_FORK_MUTEX_MALLOC));
	g->allocated.mutex_forks = 1;
	return (0);
}

/*
	 The ft_init_mutex_locks() function allocates the required area for
	 	the mutex locks and initializes them. ~used to eliminate data races~
*/
int	ft_init_mutex_locks(t_philo *g)
{
	g->is_done_mutex = (pthread_mutex_t *)
		ft_calloc(1, sizeof(pthread_mutex_t));
	if (!g->is_done_mutex)
		return (ft_error(g, ERR_DONE_MUTEX_MALLOC));
	g->allocated.mutex_is_done = 1;
	if (pthread_mutex_init(g->is_done_mutex, NULL))
		return (ft_error(g, ERR_DONE_MUTEX_INIT));
	g->exit_mutex = (pthread_mutex_t *) ft_calloc(1, sizeof(pthread_mutex_t));
	if (!g->exit_mutex)
		return (ft_error(g, ERR_EXIT_MUTEX_MALLOC));
	g->allocated.mutex_exit = 1;
	if (pthread_mutex_init(g->exit_mutex, NULL))
		return (ft_error(g, ERR_EXIT_MUTEX_INIT));
	return (0);
}

/*
	 The ft_init_philo() function allocates the required mutexes and initializes
	 	the properties of each philosopher.
*/
int	ft_init_philo(t_philo *g, int id)
{
	g->philos[id].id = id;
	g->philos[id].his_fork = id;
	g->philos[id].next_fork = (id + 1) % g->n_philos;
	g->philos[id].dead = 0;
	g->philos[id].n_of_meals = 0;
	g->philos[id].eating = (pthread_mutex_t *)
		ft_calloc(1, sizeof(pthread_mutex_t));
	if (!g->philos[id].eating)
		return (ft_error(g, ERR_EATING_MUTEX_MALLOC));
	g->allocated.mutex_eating++;
	if (pthread_mutex_init(g->philos[id].eating, NULL))
		return (ft_error(g, ERR_EATING_MUTEX_INIT));
	g->philos[id].next_meal_mutex = (pthread_mutex_t *)
		ft_calloc(1, sizeof(pthread_mutex_t));
	if (!g->philos[id].next_meal_mutex)
		return (ft_error(g, ERR_PHILO_MUTEX_MALLOC));
	g->allocated.mutex_next_meal++;
	if (pthread_mutex_init(g->philos[id].next_meal_mutex, NULL))
		return (ft_error(g, ERR_PHILO_MUTEX_INIT));
	if (pthread_mutex_init(&g->forks[id], NULL))
		return (ft_error(g, ERR_FORK_MUTEX_INIT));
	g->philos[id].philo = g;
	return (0);
}
