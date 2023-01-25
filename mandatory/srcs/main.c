/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 04:37:33 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/25 06:32:29 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
	This function destroys the mutex then frees its heap allocated area.
*/
void	ft_destroy_mutex(t_philo *g, pthread_mutex_t *mutex, char *err)
{
	if (pthread_mutex_destroy(mutex))
		ft_error(g, err);
	free(mutex);
}

/*
	Each time a pointer is allocated in the heap, it is flagged as 1 in
	the g->allocated struct, it is freed here before exiting the program,
	also all the mutexes initialized during the program are destroyed.
*/
void	ft_free_struct(t_philo *g)
{
	size_t	i;
	int		mutex_forks;

	mutex_forks = g->allocated.mutex_eating;
	ft_free_mutexes(g);
	i = -1;
	if (g->allocated.mutex_eating)
		while (++i < g->n_philos && g->allocated.mutex_eating--)
			ft_destroy_mutex(g, g->philos[i].eating, ERR_EATING_MUTEX_DESTROY);
	i = -1;
	if (g->allocated.mutex_next_meal)
		while (++i < g->n_philos && g->allocated.mutex_next_meal--)
			ft_destroy_mutex(g, g->philos[i].next_meal_mutex,
				ERR_PHILO_MUTEX_DESTROY);
	if (g->allocated.mutex_forks)
	{
		i = -1;
		while (++i < g->n_philos && mutex_forks--)
			if (pthread_mutex_destroy(&g->forks[i]))
				ft_error(g, ERR_FORK_MUTEX_DESTROY);
		free(g->forks);
	}
	if (g->allocated.philos)
		free(g->philos);
}

/*
	- The pthread_create() function starts a new thread in the calling
      process. The new thread starts execution by invoking
      ft_routine(); &g->philos[i] is passed as the sole argument of
      ft_routine(). ~ equivalent to calling ft_routine(&g->philos[i])
	  
	- The pthread_detach() function marks the thread identified by
	  thread as detached. When a detached thread terminates, its
	  resources are automatically released back to the system without
	  the need for another thread to join with the terminated thread.
*/
static int	ft_launch_thread(t_philo *g, int i)
{
	if (pthread_create(&g->philos[i].thread, NULL, &ft_routine, &g->philos[i]))
		return (ft_error(g, ERR_PHILO_THREAD_CREAT));
	if (pthread_detach(g->philos[i].thread))
		return (ft_error(g, ERR_PHILO_THREAD_DETACH));
	if (g->exit_message)
		return (1);
	if (usleep(100) == -1)
		return (ft_error(g, ERR_SLEEP));
	return (0);
}

/*
	 The main function of the program,
		we check -> parse & init -> execute -> free -> exit;
*/
int	main(int argc, char **argv)
{
	t_philo	*g;
	size_t	i;

	g = (t_philo *) ft_calloc(1, sizeof(t_philo));
	if (!g)
		return (ft_exit_error(g, ERR_STRUCT_MALLOC, 0));
	if (argc != 5 && argc != 6)
		return (ft_exit_error(g, ERR_ARGS_ARGC_INVALID, 1));
	if (ft_check_and_init(g, argc, argv))
		return (ft_exit_error(g, g->exit_message, 0));
	if (pthread_mutex_lock(g->wait))
		return (ft_exit_error(g, ERR_WAIT_MUTEX_LOCK, 0));
	i = -1;
	while (++i < g->n_philos)
		if (ft_launch_thread(g, i))
			return (ft_exit_error(g, g->exit_message, 0));
	if (pthread_mutex_lock(g->wait)){
		return (ft_exit_error(g, ERR_WAIT_MUTEX_LOCK, 0));}
	ft_free_struct(g);
	free(g);
	return (0);
}
