/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:25:19 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/21 14:11:08 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
	A function to check if a string contains a valid number of type `int`.
*/
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

/*
	The functions gettimeofday() and settimeofday() can get and set
    the time as well as a timezone.

    The `timestamp` argument is a `struct timeval` (as specified in
    <sys/time.h>):

		struct timeval
		{
			time_t		tv_sec;		// seconds
			suseconds_t	tv_usec;	// microseconds
		};
	
	and gives the number of seconds and microseconds since the Epoch
		~ January 1st, 1970 at 00:00:00 UTC is referred to as the Unix epoch.

	The `timezone` argument is a `struct timezone`:

		struct timezone
		{
			int	tz_minuteswest;		// minutes west of Greenwich
			int	tz_dsttime;			// type of DST correction
		};
*/
unsigned long	ft_get_time(t_timezone *timezone)
{
	t_timeval	timestamp;

	if (gettimeofday(&timestamp, timezone) == -1)
		return (0);
	return ((timestamp.tv_sec * 1000)
		+ (timestamp.tv_usec / 1000));
}
