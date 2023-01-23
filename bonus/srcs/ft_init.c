/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:55:06 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/23 23:39:13 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_init_struct(t_philo *g)
{
	g->philos = (t_philos *) ft_calloc(g->n_philos, sizeof(t_philos));
	if (!g->philos)
		return (ft_error(g, ERR_PHILO_MALLOC));
	g->allocated.philos = 1;
	g->start = ft_get_time(NULL);
	if (!g->start)
		return (ft_error(g, ERR_TIME));
	if (ft_init_semaphores(g))
		return (1);
	return (0);
}

int	ft_init_semaphores(t_philo *g)
{
	if (sem_unlink("/print") == -1)
		return (ft_error(g, ERR_PRINT_SEMAPH_UNLINK));
	if (sem_unlink("/wait") == -1)
		return (ft_error(g, ERR_WAIT_SEMAPH_UNLINK));
	if (sem_unlink("/forks") == -1)
		return (ft_error(g, ERR_FORKS_SEMAPH_UNLINK));
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
	return (0);
}
