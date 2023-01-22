/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:14:30 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/22 09:27:42 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
	g->forks = (pthread_mutex_t *)
		ft_calloc(g->n_philos, sizeof(pthread_mutex_t));
	if (!g->forks)
		return (ft_error(g, ERR_FORK_MUTEX_MALLOC));
	g->allocated.mutex_forks = 1;
	return (0);
}

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
	if (pthread_mutex_init(&g->forks[id], NULL))
		return (ft_error(g, ERR_FORK_MUTEX_INIT));
	g->philos[id].philo = g;
	return (0);
}
