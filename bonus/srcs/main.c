/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:08:55 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/24 02:32:17 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
	Each time a pointer is allocated in the heap, it is flagged as 1 in
	the g->allocated struct, it is freed here before exiting the program,
	also all the semaphores initialized during the program are unset.
*/
void	ft_free_struct(t_philo *g)
{
	size_t	i;

	i = -1;
	while (++i < g->n_philos && g->allocated.fork--)
		kill(g->philos[i].process, SIGKILL);
	if (g->allocated.semaph_print)
		if (sem_close(g->print) == -1)
			ft_error(g, ERR_PRINT_SEMAPH_CLOSE);
	if (g->allocated.semaph_wait)
		if (sem_close(g->wait) == -1)
			ft_error(g, ERR_WAIT_SEMAPH_CLOSE);
	if (g->allocated.semaph_forks)
		if (sem_close(g->forks) == -1)
			ft_error(g, ERR_FORKS_SEMAPH_CLOSE);
	if (g->allocated.semaph_check)
		if (sem_close(g->check) == -1)
			ft_error(g, ERR_CHECK_SEMAPH_CLOSE);
	if (g->allocated.semaph_meals)
		if (sem_close(g->meals) == -1)
			ft_error(g, ERR_MEALS_SEMAPH_CLOSE);
	if (g->allocated.philos)
		free(g->philos);
}

static int	ft_launch_process(t_philo *g, int i)
{
	g->philos[i].process = fork();
	if (g->philos[i].process == -1)
		return (ft_error(g, ERR_PHILO_PROCESS_FORK));
	if (g->philos[i].process == 0)
		ft_routine(g, &g->philos[i]);
	g->allocated.fork++;
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
	t_philo	g;
	size_t	i;

	if (argc != 5 && argc != 6)
		return (ft_exit_error(&g, ERR_ARGS_ARGC_INVALID, 1));
	if (ft_check_and_init(&g, argc, argv))
		return (ft_exit_error(&g, g.exit_message, 0));
	if (sem_wait(g.wait) == -1)
		return (ft_exit_error(&g, ERR_WAIT_SEMAPH_WAIT, 0));
	i = -1;
	while (++i < g.n_philos)
		if (ft_launch_process(&g, i))
			return (ft_exit_error(&g, g.exit_message, 0));
	if (sem_wait(g.wait) == -1)
		return (ft_exit_error(&g, ERR_WAIT_SEMAPH_WAIT, 0));
	ft_free_struct(&g);
	return (0);
}
