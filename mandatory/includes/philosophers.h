/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 03:04:46 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/18 21:00:52 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>

# define UNINITIALIZED -1
# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define ITALIC "\x1B[3m"
# define RESET "\x1B[0m"

typedef struct s_timeval
{
	time_t		sec;
	suseconds_t	usec;
}	t_timeval;

typedef struct s_philos
{
	int			id;
	pthread_t	thread;
	// int			left_fork;
	// int			right_fork;
	int			n_of_meals;
	t_timeval	last_meal;
}	t_philos;

typedef struct s_routine
{
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			n_of_times;
}	t_routine;

typedef struct s_alloc
{
	int	philos;
}	t_alloc;

typedef struct s_philo
{
	t_philos	*philos;
	t_routine	routine;
	size_t		n_philos;
	int			limited_meals;
	char		*exit_message;
	t_alloc		allocated;
}	t_philo;

/* ---------------- ERRORS ---------------- */
int		ft_error(t_philo *g, char *str);
void	ft_exit_error(t_philo *g, char *str, int usage);

/* ---------------- UTILS ---------------- */
void	*ft_routine(t_philos *philo);
void	ft_free_struct(t_philo *g);
int		ft_is_valid_timestamps(t_philo *g, char **argv);
int		ft_check_and_init(t_philo *g, int argc, char **argv);
int		ft_isint(char *str);
int		ft_init_struct(t_philo *g);

/* ---------------- FUNCTIONS ---------------- */
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str);

#endif