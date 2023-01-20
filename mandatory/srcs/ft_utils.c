/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:25:19 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/20 15:29:07 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_isint(char *str)
{
	long int	n;
	int			s;
	int			i;

	if (str[0] == '\0')
		return (0);
	n = 0;
	s = 1;
	i = -1;
	while (str[++i] == 32 || (8 < str[i] && str[i] < 14))
		;
	if (str[i] == 43 || str[i] == 45)
		if (str[i++] == 45)
			s *= -1;
	while (str[i])
	{
		if (!(47 < str[i] && str[i] < 58))
			return (0);
		n = n * 10 + str[i++] - 48;
	}
	return ((n * s) <= INT_MAX && (n * s) >= INT_MIN);
}

unsigned long	ft_get_time(void *options)
{
	t_timeval	timestamp;

	gettimeofday(&timestamp, options);
	return ((timestamp.tv_sec * 1000)
		+ (timestamp.tv_usec / 1000));
}
