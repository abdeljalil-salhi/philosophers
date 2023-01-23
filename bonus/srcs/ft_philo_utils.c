/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:51:59 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/23 14:53:15 by absalhi          ###   ########.fr       */
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
			return (ft_error(g, ERR_ARGS_NUMBER_INVALID));
	i = ft_atoi(argv[1]);
	if (i < 1)
		return (ft_error(g, ERR_ARGS_PHILO_MINIMUM));
	g->n_philos = i;
	g->routine.time_to_die = ft_atoi(argv[2]);
	g->routine.time_to_eat = ft_atoi(argv[3]);
	g->routine.time_to_sleep = ft_atoi(argv[4]);
	if (g->routine.time_to_die < 60 || g->routine.time_to_eat < 60
		|| g->routine.time_to_sleep < 60)
		return (ft_error(g, ERR_ARGS_NUMBER_MINIMUM));
	if (g->limited_meals)
		g->routine.n_of_times = ft_atoi(argv[5]);
	else
		g->routine.n_of_times = DEFAULT;
	if (g->limited_meals && g->routine.n_of_times < 1)
		return (ft_error(g, ERR_ARGS_MEALS_MINIMUM));
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

/*
	 The ft_print_action() function responsible of printing the right message
	 	for the `int action` passed as argument.
*/
int	ft_print_action(t_philo *g, t_philos *philo, int action)
{
	unsigned long	_time;

	_time = ft_get_time(NULL);
	if (!_time)
		return (ft_error(g, ERR_TIME));
	_time -= g->start;
	if (action == DEAD)
		ft_format(_time, philo->id + 1, "died", 0);
	else if (action == TOOK_FORK)
		ft_format(_time, philo->id + 1, "has taken a fork", 0);
	else if (action == EATING)
		ft_format(_time, philo->id + 1, "is eating", 0);
	else if (action == SLEEPING)
		ft_format(_time, philo->id + 1, "is sleeping", 0);
	else if (action == THINKING)
		ft_format(_time, philo->id + 1, "is thinking", 0);
	else if (action == IS_DONE)
		ft_format(_time, 0, NULL, 1);
	return (0);
}
