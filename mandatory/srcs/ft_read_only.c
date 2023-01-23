/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_only.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:25:20 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/23 16:39:33 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_safe_read_is_done(t_philo *g)
{
	int	_read;

	if (pthread_mutex_lock(g->is_done_mutex))
		return (ft_error(g, ERR_DONE_MUTEX_LOCK));
	_read = g->is_done;
	if (pthread_mutex_unlock(g->is_done_mutex))
		return (ft_error(g, ERR_DONE_MUTEX_UNLOCK));
	return (_read);
}

char	*ft_safe_read_exit_message(t_philo *g)
{
	char	*_read;

	if (pthread_mutex_lock(g->exit_mutex))
		return (ft_perror(g, ERR_EXIT_MUTEX_LOCK));
	_read = g->exit_message;
	if (pthread_mutex_unlock(g->exit_mutex))
		return (ft_perror(g, ERR_EXIT_MUTEX_UNLOCK));
	return (_read);
}
