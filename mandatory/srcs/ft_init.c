/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:14:30 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/18 21:04:12 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_init_struct(t_philo *g)
{
	size_t	i;
	
	g->philos = (t_philos *) ft_calloc(g->n_philos, sizeof(t_philos));
	g->allocated.philos = 1;
	if (!g->philos)
		return (ft_error(g, "Error allocating the philosophers."));
	i = -1;
	while (++i < g->n_philos)
	{
		g->philos[i].id = i;
		if (pthread_create(&g->philos[i].thread, 0, &ft_routine, (void *) &g->philos[i]))
			return (ft_error(g, "Error creating the threads."));
	}
	return (0);
}
