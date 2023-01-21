/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 03:15:58 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/21 11:20:30 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
	 The ft_error() function sets the `g->exit_message` to the passed string
		as argument `char *str` and returns 1.
*/
int	ft_error(t_philo *g, char *str)
{
	g->exit_message = str;
	return (1);
}

/*
	 The ft_perror() function sets the `g->exit_message` to the passed string
		as argument `char *str` and returns NULL (0x0).
*/
void	*ft_perror(t_philo *g, char *str)
{
	g->exit_message = str;
	return (NULL);
}

/*
	 The ft_exit_error() function prints the error passed as argument
	 	`char *str` in the standard error, prints the usage if the
		`int usage` parameter is flagged as true, frees the `t_philo`
		struct and returns 1.
*/
int	ft_exit_error(t_philo *g, char *str, int usage)
{
	write(2, RED, ft_strlen(RED));
	write(2, "Error:\t", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	write(2, RESET, ft_strlen(RESET));
	if (usage)
	{
		printf(GREEN "\nUsage:\t" RESET);
		printf(ITALIC "./philo number_of_philosophers time_to_die\n");
		printf("\t        time_to_eat time_to_sleep\n");
		printf("\t        [number_of_times_each_philosopher_must_eat]\n" RESET);
	}
	ft_free_struct(g);
	return (1);
}
