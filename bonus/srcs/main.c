/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:08:55 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/23 14:51:44 by absalhi          ###   ########.fr       */
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
	(void) g;
}

/*
	 The main function of the program,
		we check -> parse & init -> execute -> free -> exit;
*/
int	main(int argc, char **argv)
{
	t_philo	g;

	if (argc != 5 && argc != 6)
		return (ft_exit_error(&g, ERR_ARGS_ARGC_INVALID, 1));
	if (ft_check_and_init(&g, argc, argv))
		return (ft_exit_error(&g, g.exit_message, 0));
	return (0);
}
