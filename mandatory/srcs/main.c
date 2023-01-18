/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 04:37:33 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/18 18:47:57 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_free_struct(t_philo *g)
{
	if (g->allocated.philos)
		free(g->philos);
}

int	main(int argc, char **argv)
{
	t_philo	g;

	if (argc != 5 && argc != 6)
		ft_exit_error(&g, "Invalid number of arguments.", 1);
	if (ft_check_and_init(&g, argc, argv))
		ft_exit_error(&g, g.exit_message, 0);
	return (0);
}
