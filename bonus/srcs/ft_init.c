/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:55:06 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/24 02:36:36 by absalhi          ###   ########.fr       */
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
	if (ft_init_semaphores(g))
		return (1);
	i = -1;
	while (++i < g->n_philos)
		if (ft_init_philo(g, i))
			return (1);
	return (0);
}

static void	ft_unlink_semaphores(void)
{
	sem_unlink("/print");
	sem_unlink("/wait");
	sem_unlink("/forks");
	sem_unlink("/check");
	sem_unlink("/meals");
}

int	ft_init_semaphores(t_philo *g)
{
	ft_unlink_semaphores();
	g->print = sem_open("/print", O_CREAT, 0644, 1);
	if (g->print == SEM_FAILED)
		return (ft_error(g, ERR_PRINT_SEMAPH_OPEN));
	g->allocated.semaph_print = 1;
	g->wait = sem_open("/wait", O_CREAT, 0644, 1);
	if (g->wait == SEM_FAILED)
		return (ft_error(g, ERR_WAIT_SEMAPH_OPEN));
	g->allocated.semaph_wait = 1;
	g->forks = sem_open("/forks", O_CREAT, 0644, g->n_philos);
	if (g->forks == SEM_FAILED)
		return (ft_error(g, ERR_FORKS_SEMAPH_OPEN));
	g->allocated.semaph_forks = 1;
	g->check = sem_open("/check", O_CREAT, 0644, 1);
	if (g->check == SEM_FAILED)
		return (ft_error(g, ERR_CHECK_SEMAPH_OPEN));
	g->allocated.semaph_check = 1;
	g->meals = sem_open("/meals", O_CREAT, 0644, 0);
	if (g->meals == SEM_FAILED)
		return (ft_error(g, ERR_MEALS_SEMAPH_OPEN));
	g->allocated.semaph_meals = 1;
	return (0);
}

int	ft_init_philo(t_philo *g, int id)
{
	g->philos[id].id = id;
	g->philos[id].dead = 0;
	g->philos[id].philo = g;
	return (0);
}
