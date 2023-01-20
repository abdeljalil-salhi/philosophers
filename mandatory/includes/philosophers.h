/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 03:04:46 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/20 15:47:52 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

# define UNINITIALIZED -1
# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define ITALIC "\x1B[3m"
# define RESET "\x1B[0m"

typedef struct timeval	t_timeval;

typedef struct s_philos
{
	int				id;
	pthread_t		thread;
	int				his_fork;
	int				next_fork;
	int				n_of_meals;
	t_timeval		last_meal;
	int				dead;
	pthread_mutex_t	*eating;
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
	int	mutex_print;
	int	mutex_eating;
	int	mutex_forks;
}	t_alloc;

typedef struct s_philo
{
	t_philos		*philos;
	t_routine		routine;
	size_t			n_philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	unsigned long	start;
	int				limited_meals;
	char			*exit_message;
	t_alloc			allocated;
}	t_philo;

/* ---------------- ERRORS ---------------- */
int				ft_error(t_philo *g, char *str);
int				ft_exit_error(t_philo *g, char *str, int usage);

/* ---------------- UTILS ---------------- */
void			*ft_routine(void *philo);
void			ft_free_struct(t_philo *g);
int				ft_is_valid_timestamps(t_philo *g, char **argv);
int				ft_check_and_init(t_philo *g, int argc, char **argv);
int				ft_isint(char *str);
unsigned long	ft_get_time(void *options);
int				ft_init_struct(t_philo *g);

/* ---------------- FUNCTIONS ---------------- */
size_t			ft_strlen(const char *s);
void			*ft_calloc(size_t count, size_t size);
int				ft_atoi(const char *str);

#endif