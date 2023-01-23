/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 21:34:35 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/23 21:46:49 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*ft_routine_invalid(t_philo *g, t_philos *philo)
{
	if (pthread_mutex_unlock(philo->next_meal_mutex))
		return (ft_perror(g, ERR_PHILO_MUTEX_UNLOCK));
	if (pthread_mutex_lock(g->is_done_mutex))
		return (ft_perror(g, ERR_DONE_MUTEX_LOCK));
	g->is_done = 1;
	if (pthread_mutex_unlock(g->is_done_mutex))
		return (ft_perror(g, ERR_DONE_MUTEX_UNLOCK));
	if (pthread_mutex_lock(philo->eating))
		return (ft_perror(g, ERR_EATING_MUTEX_LOCK));
	if (ft_print_action(g, philo, DEAD))
		return (NULL);
	if (pthread_mutex_unlock(g->wait))
		return (ft_perror(g, ERR_WAIT_MUTEX_UNLOCK));
	return (NONULL);
}

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
