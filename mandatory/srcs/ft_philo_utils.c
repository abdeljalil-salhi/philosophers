/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 03:21:42 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/21 14:14:57 by absalhi          ###   ########.fr       */
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
	if (!g->n_philos)
		return (ft_error(g, "You need at least one philosopher to start."));
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

/*
	 The ft_print_action() function responsible of printing the right message
	 	for the `int action` passed as argument.
*/
int	ft_print_action(t_philo *g, t_philos *philo, int action)
{
	unsigned long	_time;

	if (pthread_mutex_lock(g->print))
		return (ft_error(g, "Error while locking the print mutex."));
	_time = ft_get_time(NULL);
	if (!_time)
		return (ft_error(g, "Error while getting the time of the system."));
	_time -= g->start;
	if (action == DEAD)
		printf("%5lums philosopher %d died\n", _time, philo->id + 1);
	else if (action == TOOK_FORK)
		printf("%5lums philosopher %d has taken a fork\n", _time, philo->id + 1);
	else if (action == EATING)
		printf("%5lums philosopher %d is eating\n", _time, philo->id + 1);
	else if (action == SLEEPING)
		printf("%5lums philosopher %d is sleeping\n", _time, philo->id + 1);
	else if (action == THINKING)
		printf("%5lums philosopher %d is thinking\n", _time, philo->id + 1);
	else if (action == IS_DONE)
		printf("%5lums philosophers finished dinning\n", _time);
	if (action < DEAD)
		if (pthread_mutex_unlock(g->print))
			return (ft_error(g, "Error while unlocking the print mutex."));
	return (0);
}

void	*ft_routine_if_valid(void *philo)
{
	t_sroutine	s;

	s.casted = (t_philos *) philo;
	(void) s.check;
	while (1)
	{
		s._time = ft_get_time(NULL);
		if (!s._time)
			return (ft_perror(s.casted->philo,
					"Error while getting the time of the system."));
		if (s.casted->next_meal < s._time)
		{
			s.casted->philo->is_done = 1;
			if (pthread_mutex_lock(s.casted->eating))
				return (ft_perror(s.casted->philo,
						"Error while locking the eating mutex."));
			if (ft_print_action(s.casted->philo, s.casted, DEAD))
				return (NULL);
			if (pthread_mutex_unlock(s.casted->philo->wait))
				return (ft_perror(s.casted->philo,
						"Error while unlocking the wait mutex."));
			break ;
		}
	}
	return (NULL);
}

int	ft_routine_if_done(t_philo *g, t_philos *philo)
{
	int		all;
	size_t	i;

	if (g->limited_meals)
	{
		all = 1;
		i = -1;
		while (++i < g->n_philos)
			if (g->philos[i].n_of_meals < g->routine.n_of_times)
				all = 0;
		if (all)
		{
			g->is_done = 1;
			if (pthread_mutex_lock(philo->eating))
				return (ft_error(g, "Error while locking eating mutex."));
			if (ft_print_action(g, philo, IS_DONE))
				return (1);
			if (pthread_mutex_unlock(g->wait))
				return (ft_error(g, "Error while unlocking wait mutex."));
			return (2);
		}
	}
	return (0);
}
