/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 03:15:58 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/18 18:42:05 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_error(t_philo *g, char *str)
{
	g->exit_message = str;
	return (1);
}

void	ft_exit_error(t_philo *g, char *str, int usage)
{
	write(2, RED, ft_strlen(RED));
	write(2, "Error:\t", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n\n", 2);
	write(2, RESET, ft_strlen(RESET));
	if (usage)
	{
		printf(GREEN "Usage:\t" RESET);
		printf(ITALIC "./philo number_of_philosophers time_to_die\n");
		printf("\t        time_to_eat time_to_sleep\n");
		printf("\t        [number_of_times_each_philosopher_must_eat]\n" RESET);
	}
	ft_free_struct(g);
	exit(1);
}
