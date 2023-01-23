/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:53:35 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/23 14:54:03 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
	 The function ft_format() prints the action to the standard output
	 	with colors.
*/
void	ft_format(unsigned long timestamp, int id, char *log, int done)
{
	printf(GREEN "%10lums" RESET, timestamp);
	printf(YELLOW "  |  " RESET);
	if (done)
		printf(GREEN "philosophers finished dinning\n" RESET);
	else
	{
		printf("philosopher");
		printf(BLUE " %d " RESET, id);
		printf("%s\n", log);
	}
}
