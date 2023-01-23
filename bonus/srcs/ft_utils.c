/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:53:35 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/23 22:15:32 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
