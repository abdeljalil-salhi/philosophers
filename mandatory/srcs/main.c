/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 04:37:33 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/21 13:49:11 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
	A function to visualize our `t_philo` struct, it helps during debugging.
*/
void	ft_print_struct(t_philo *g)
{
	printf("struct s_philo:\n");
	printf("\tt_philos        *philos: %p\n", g->philos);
	printf("\tstruct s_routine routine:\n");
	printf("\t\tint time_to_die: %d\n", g->routine.time_to_die);
	printf("\t\tint time_to_eat: %d\n", g->routine.time_to_eat);
	printf("\t\tint time_to_sleep: %d\n", g->routine.time_to_sleep);
	printf("\t\tint n_of_times: %d\n", g->routine.n_of_times);
	printf("\tsize_t           n_philos: %zu\n", g->n_philos);
	printf("\tint              limited_meals: %d\n", g->limited_meals);
	printf("\tchar            *exit_message: %s\n", g->exit_message);
	printf("\tstruct s_alloc:\n");
	printf("\t\tint philos: %d\n\n", g->allocated.philos);
	printf("\t\tint mutex_print: %d\n\n", g->allocated.mutex_print);
	printf("\t\tint mutex_wait: %d\n\n", g->allocated.mutex_wait);
	printf("\t\tint mutex_eating: %d\n\n", g->allocated.mutex_eating);
	printf("\t\tint mutex_forks: %d\n\n", g->allocated.mutex_forks);
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
	if (g->allocated.philos)
		free(g->philos);
	if (g->allocated.mutex_print)
	{
		if (pthread_mutex_destroy(g->print))
			ft_error(g, "Error destroying the print mutex.");
		free(g->print);
	}
	if (g->allocated.mutex_wait)
	{
		if (pthread_mutex_destroy(g->wait))
			ft_error(g, "Error destroying the wait mutex.");
		free(g->wait);
	}
	if (g->allocated.mutex_eating)
	{
		i = -1;
		while (++i < g->n_philos && g->allocated.mutex_eating--)
		{
			if (pthread_mutex_destroy(g->philos[i].eating))
				ft_error(g, "Error destroying the eating mutex.");
			free(g->philos[i].eating);
		}
	}
	if (g->allocated.mutex_forks)
	{
		i = -1;
		while (++i < g->n_philos && mutex_forks--)
			if (pthread_mutex_destroy(&g->forks[i]))
				ft_error(g, "Error destroying the forks mutex.");
		free(g->forks);
	}
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
		return (ft_error(g, "Error while creating the threads."));
	if (pthread_detach(g->philos[i].thread))
		return (ft_error(g, "Error while detaching the threads."));
	if (g->exit_message)
		return (1);
	if (usleep(100) == -1)
		return (ft_error(g, "Error while system sleeping."));
	return (0);
}

/*
	 The main function of the program,
		we check -> parse & init -> execute -> free -> exit;
*/
int	main(int argc, char **argv)
{
	t_philo	g;
	size_t	i;

	if (argc != 5 && argc != 6)
		return (ft_exit_error(&g, "Invalid number of arguments.", 1));
	if (ft_check_and_init(&g, argc, argv))
		return (ft_exit_error(&g, g.exit_message, 0));
	if (pthread_mutex_lock(g.wait))
		return (ft_exit_error(&g, "Error while locking the wait mutex.", 0));
	i = -1;
	while (++i < g.n_philos)
		if (ft_launch_thread(&g, i))
			return(ft_exit_error(&g, g.exit_message, 0));
	if (pthread_mutex_lock(g.wait))
		return (ft_exit_error(&g, "Error while locking the wait mutex.", 0));
	ft_free_struct(&g);
	return (0);
}
