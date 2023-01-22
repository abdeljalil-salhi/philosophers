/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:57:03 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/22 09:21:09 by absalhi          ###   ########.fr       */
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
		return (ft_perror(s.casted->philo, ERR_TIME));
	s.casted->next_meal = s._time + s.casted->philo->routine.time_to_die;
	if (pthread_create(&s.check, NULL, &ft_routine_if_valid, s.casted))
		return (ft_perror(s.casted->philo, ERR_CHECK_THREAD_CREAT));
	if (s.casted->philo->exit_message)
		return (NULL);
	if (pthread_detach(s.check))
		return (ft_perror(s.casted->philo, ERR_CHECK_THREAD_DETACH));
	while (1)
	{
		_case = ft_repetitive_routine(s.casted->philo, s.casted);
		if (_case == 2)
			return (NULL);
		else if (_case)
			break ;
	}
	return (NULL);
}

int	ft_repetitive_routine(t_philo *g, t_philos *philo)
{
	int	_case;

	if (g->is_done)
		return (1);
	if (ft_take_forks(g, philo))
		return (2);
	if (ft_eat(g, philo))
		return (2);
	_case = ft_routine_if_done(g, philo);
	if (_case == 2)
		return (1);
	else if (_case)
		return (2);
	if (ft_sleep(g, philo))
		return (2);
	if (ft_print_action(g, philo, THINKING))
		return (2);
	return (0);
}

int	ft_take_forks(t_philo *g, t_philos *philo)
{
	if (pthread_mutex_lock(g->forks + philo->his_fork))
		return (ft_error(g, ERR_FORK_MUTEX_LOCK));
	if (ft_print_action(g, philo, TOOK_FORK))
		return (1);
	if (pthread_mutex_lock(g->forks + philo->next_fork))
		return (ft_error(g, ERR_FORK_MUTEX_LOCK));
	if (ft_print_action(g, philo, TOOK_FORK))
		return (1);
	return (0);
}

int	ft_eat(t_philo *g, t_philos *philo)
{
	if (pthread_mutex_lock(philo->eating))
		return (ft_error(g, ERR_EATING_MUTEX_LOCK));
	if (ft_print_action(g, philo, EATING))
		return (1);
	philo->n_of_meals++;
	philo->ate_at = ft_get_time(NULL);
	if (!philo->ate_at)
		return (ft_error(g, ERR_TIME));
	philo->next_meal = philo->ate_at + (unsigned long) g->routine.time_to_die;
	if (usleep(g->routine.time_to_eat * 1000) == -1)
		return (ft_error(g, ERR_SLEEP));
	if (pthread_mutex_unlock(g->forks + philo->his_fork))
		return (ft_error(g, ERR_FORK_MUTEX_UNLOCK));
	if (pthread_mutex_unlock(g->forks + philo->next_fork))
		return (ft_error(g, ERR_FORK_MUTEX_UNLOCK));
	if (pthread_mutex_unlock(philo->eating))
		return (ft_error(g, ERR_EATING_MUTEX_UNLOCK));
	return (0);
}

int	ft_sleep(t_philo *g, t_philos *philo)
{
	if (usleep(10) == -1)
		return (ft_error(g, ERR_SLEEP));
	if (ft_print_action(g, philo, SLEEPING))
		return (1);
	if (usleep(g->routine.time_to_sleep * 1000) == -1)
		return (ft_error(g, ERR_SLEEP));
	return (0);
}
