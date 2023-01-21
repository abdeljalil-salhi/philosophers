/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:34:57 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/21 07:41:17 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
	 The ft_strlen() function calculates the length of the string pointed
       to by `const char *s`, excluding the terminating null byte ('\0').
*/
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

/*
	 The ft_calloc() function shall allocate unused space for an array of
       `size_t count` elements each of whose size in bytes is `size_t size`.
	   The space shall be initialized to all bits 0.
*/
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

/*
	 The ft_atoi() function converts the initial portion of the string
       pointed to by `const char *str` to `int`.
*/
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
