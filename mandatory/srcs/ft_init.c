/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:14:30 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/18 18:32:12 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_init_struct(t_philo *g)
{
	g->philos = (t_philos *) ft_calloc(g->n_philos, sizeof(t_philos));
	g->allocated.philos = 1;
	if (!g->philos)
		return (ft_error(g, "Error allocating the philosophers."));
	return (0);
}
