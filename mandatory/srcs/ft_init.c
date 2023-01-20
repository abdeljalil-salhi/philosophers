/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:14:30 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/20 15:47:39 by absalhi          ###   ########.fr       */
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
	g->print = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!g->print)
		return (ft_error(g, "Error allocating the print mutex."));
	g->allocated.mutex_print = 1;
	g->forks = ft_calloc(g->n_philos, sizeof(pthread_mutex_t));
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
		g->philos[i].eating = ft_calloc(1, sizeof(pthread_mutex_t));
		if (!g->philos[i].eating)
			return (ft_error(g, "Error allocating the eating mutex."));
		pthread_mutex_init(g->philos[i].eating, NULL);
		if (pthread_create(&g->philos[i].thread, 0, &ft_routine, &g->philos[i]))
			return (ft_error(g, "Error creating the threads."));
	}
	g->allocated.mutex_eating = 1;
	return (0);
}
