/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:14:30 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/21 07:31:48 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_init_struct(t_philo *g)
{
	size_t	i;

	g->philos = (t_philos *) ft_calloc(g->n_philos, sizeof(t_philos));
	if (!g->philos)
		return (ft_error(g, "Error allocating the philosophers."));
	g->allocated.philos = 1;
	g->start = ft_get_time(NULL);
	if (!g->start)
		return (ft_error(g, "Error while getting the time of the system."));
	g->print = (pthread_mutex_t *) ft_calloc(1, sizeof(pthread_mutex_t));
	if (!g->print)
		return (ft_error(g, "Error allocating the print mutex."));
	g->allocated.mutex_print = 1;
	g->forks = (pthread_mutex_t *)
		ft_calloc(g->n_philos, sizeof(pthread_mutex_t));
	if (!g->forks)
		return (ft_error(g, "Error allocating the forks mutexes."));
	g->allocated.mutex_forks = 1;
	i = -1;
	while (++i < g->n_philos)
	{
		g->philos[i].id = i;
		g->philos[i].his_fork = i;
		g->philos[i].next_fork = (i + 1) % g->n_philos;
		g->philos[i].dead = 0;
		g->philos[i].n_of_meals = 0;
		g->philos[i].eating = (pthread_mutex_t *)
			ft_calloc(1, sizeof(pthread_mutex_t));
		if (!g->philos[i].eating)
			return (ft_error(g, "Error allocating the eating mutex."));
		g->allocated.mutex_eating++;
		if (pthread_mutex_init(g->philos[i].eating, NULL))
			return (ft_error(g, "Error initializing the eating mutex."));
		if (pthread_mutex_init(&g->forks[i], NULL))
			return (ft_error(g, "Error initializing the forks mutex."));
		g->philos[i].philo = g;
	}
	return (0);
}
