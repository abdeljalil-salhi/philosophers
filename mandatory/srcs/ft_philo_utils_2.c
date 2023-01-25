/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 21:34:35 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/25 06:37:46 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
	 The ft_routine_invalid() function checks if a philosopher is dead
	 	and unlocks the main wait mutex.
*/
int	ft_routine_invalid(t_philo *g, t_philos *philo)
{
	if (pthread_mutex_unlock(philo->next_meal_mutex))
		return (ft_error(g, ERR_PHILO_MUTEX_UNLOCK));
	if (pthread_mutex_lock(g->is_done_mutex))
		return (ft_error(g, ERR_DONE_MUTEX_LOCK));
	g->is_done = 1;
	if (pthread_mutex_unlock(g->is_done_mutex))
		return (ft_error(g, ERR_DONE_MUTEX_UNLOCK));
	if (pthread_mutex_lock(philo->eating))
		return (ft_error(g, ERR_EATING_MUTEX_LOCK));
	if (ft_print_action(g, philo, DEAD))
		return (1);
	if (pthread_mutex_unlock(g->wait))
		return (ft_error(g, ERR_WAIT_MUTEX_UNLOCK));
	return (0);
}

/*
	 The ft_free_mutexes() function destroys the mutexes and frees their
	 	allocated heap-memory afterwards.
*/
void	ft_free_mutexes(t_philo *g)
{
	if (g->allocated.mutex_print)
		ft_destroy_mutex(g, g->print, ERR_PRINT_MUTEX_DESTROY);
	if (g->allocated.mutex_wait)
		ft_destroy_mutex(g, g->wait, ERR_WAIT_MUTEX_DESTROY);
	if (g->allocated.mutex_is_done)
		ft_destroy_mutex(g, g->is_done_mutex, ERR_DONE_MUTEX_DESTROY);
	if (g->allocated.mutex_exit)
		ft_destroy_mutex(g, g->exit_mutex, ERR_EXIT_MUTEX_DESTROY);
}
