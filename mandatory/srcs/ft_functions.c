/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:34:57 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/20 13:37:21 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = -1;
	while (s[++i])
		;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tab;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	tab = (unsigned char *) malloc(count * size);
	if (!tab)
		return (NULL);
	memset(tab, '\0', size * count);
	return ((void *) tab);
}

int	ft_atoi(const char *str)
{
	int	n;
	int	i;
	int	s;

	s = 1;
	n = 0;
	i = 0;
	while (str[i] == 32 || (8 < str[i] && str[i] < 14))
		i++;
	if (str[i] == 43 || str[i] == 45)
		if (str[i++] == 45)
			s *= -1;
	while (47 < str[i] && str[i] < 58)
		n = n * 10 + str[i++] - 48;
	return (n * s);
}
