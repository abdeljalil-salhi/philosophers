/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:57:03 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/21 13:57:15 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*ft_routine(void *philo)
{
	t_sroutine	s;
	int			_case;

	s.casted = (t_philos *) philo;
	s._time = ft_get_time(NULL);
	if (!s._time)
		return (ft_perror(s.casted->philo,
				"Error while getting the time of the system."));
	s.casted->next_meal = s._time + s.casted->philo->routine.time_to_die;
	if (pthread_create(&s.check, NULL, &ft_routine_if_valid, s.casted))
		return (ft_perror(s.casted->philo,
				"Error while creating check thread."));
	if (s.casted->philo->exit_message)
		return (NULL);
	if (pthread_detach(s.check))
		return (ft_perror(s.casted->philo,
				"Error while detaching the check thread."));
	while (1)
	{
		if (s.casted->philo->is_done)
			break ;
		if (ft_take_forks(s.casted->philo, s.casted))
			return (NULL);
		if (ft_eat(s.casted->philo, s.casted))
			return (NULL);
		_case = ft_routine_if_done(s.casted->philo, s.casted);
		if (_case == 2)
			break;
		else if (_case)
			return (NULL);
		if (ft_sleep(s.casted->philo, s.casted))
			return (NULL);
		if (ft_print_action(s.casted->philo, s.casted, THINKING))
			return (NULL);
	}
	return (NULL);
}

int	ft_take_forks(t_philo *g, t_philos *philo)
{
	if (pthread_mutex_lock(g->forks + philo->his_fork))
		return (ft_error(g, "Error while locking fork mutex."));
	if (ft_print_action(g, philo, TOOK_FORK))
		return (1);
	if (pthread_mutex_lock(g->forks + philo->next_fork))
		return (ft_error(g, "Error while locking fork mutex."));
	if (ft_print_action(g, philo, TOOK_FORK))
		return (1);
	return (0);
}

int	ft_eat(t_philo *g, t_philos *philo)
{
	if (pthread_mutex_lock(philo->eating))
		return (ft_error(g, "Error while locking eating mutex."));
	if (ft_print_action(g, philo, EATING))
		return (1);
	philo->n_of_meals++;
	philo->ate_at = ft_get_time(NULL);
	if (!philo->ate_at)
		return (ft_error(g, "Error while getting the time of the system."));
	philo->next_meal = philo->ate_at + (unsigned long) g->routine.time_to_die;
	if (usleep(g->routine.time_to_eat * 1000) == -1)
		return (ft_error(g, "Error while system sleeping."));
	if (pthread_mutex_unlock(g->forks + philo->his_fork))
		return (ft_error(g, "Error while unlocking fork mutex."));
	if (pthread_mutex_unlock(g->forks + philo->next_fork))
		return (ft_error(g, "Error while unlocking fork mutex."));
	if (pthread_mutex_unlock(philo->eating))
		return (ft_error(g, "Error while unlocking eating mutex."));
	return (0);
}

int	ft_sleep(t_philo *g, t_philos *philo)
{
	if (usleep(10) == -1)
		return (ft_error(g, "Error while system sleeping."));
	if (ft_print_action(g, philo, SLEEPING))
		return (1);
	if (usleep(g->routine.time_to_sleep * 1000) == -1)
		return (ft_error(g, "Error while system sleeping."));
	return (0);
}
