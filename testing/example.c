/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 04:37:33 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/18 03:12:52 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/includes/philosophers.h"

long long int	test = 0;

void	*routine(void *arg)
{
	(void) arg;
	for (long long int i = 0; i < 1000000000000000; i++)
		test++;

	for (long long int i = 0; i < 1000000000000000; i++)
		test--;

	for (long long int i = 0; i < 1000000000000000; i++)
		test++;
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t	t1;
	pthread_t	t2;
	(void) argc, (void) argv;

	if (pthread_create(&t1, 0, &routine, 0))
		return (1);
	if (pthread_create(&t2, 0, &routine, 0))
		return (1);
	if (pthread_join(t1, 0))
		return (1);
	if (pthread_join(t2, 0))
		return (1);
	printf("%lld\n", test);
	return (0);
}