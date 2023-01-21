/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 03:21:42 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/21 07:46:28 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
	 The ft_is_valid_timestamps() function to check if the arguments are
		valid numbers of type `int`.
	 If so; it parses them into my `routine` struct,
		otherwise, it returns an error.
*/
int	ft_is_valid_timestamps(t_philo *g, char **argv)
{
	int	i;

	i = 0;
	while (++i < 5 + g->limited_meals)
		if (!ft_isint(argv[i]))
			return (ft_error(g, "One of the arguments isn't a valid number."));
	g->n_philos = ft_atoi(argv[1]);
	g->routine.time_to_die = ft_atoi(argv[2]);
	g->routine.time_to_eat = ft_atoi(argv[3]);
	g->routine.time_to_sleep = ft_atoi(argv[4]);
	if (g->limited_meals)
		g->routine.n_of_times = ft_atoi(argv[5]);
	else
		g->routine.n_of_times = DEFAULT;
	return (0);
}

/*
	 The ft_check_and_init() function responsible of checking if
		the arguments are valid, then parsing them into my `s_philo` struct.
	 It returns 0 for success. On error, 1 is returned and `g->exit_message`
		is set to indicate the error.
*/
int	ft_check_and_init(t_philo *g, int argc, char **argv)
{
	memset(g, 0, sizeof(t_philo));
	g->limited_meals = (argc == 6);
	if (ft_is_valid_timestamps(g, argv))
		return (1);
	if (ft_init_struct(g))
		return (1);
	return (0);
}
