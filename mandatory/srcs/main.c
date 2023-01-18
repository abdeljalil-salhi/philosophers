/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 04:37:33 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/18 21:03:39 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
	system("leaks philo");
}

void	ft_free_struct(t_philo *g)
{
	if (g->allocated.philos)
		free(g->philos);
}

int	main(int argc, char **argv)
{
	t_philo	g;
	size_t	i;

	if (argc != 5 && argc != 6)
		ft_exit_error(&g, "Invalid number of arguments.", 1);
	if (ft_check_and_init(&g, argc, argv))
		ft_exit_error(&g, g.exit_message, 0);
	i = -1;
	while (++i < g.n_philos)
		if (pthread_join(g.philos[i].thread, 0))
			ft_exit_error(&g, "Error while joining the threads.", 0);
	ft_print_struct(&g);
	return (0);
}
