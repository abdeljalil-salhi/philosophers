/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:50:49 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/23 23:42:05 by absalhi          ###   ########.fr       */
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
#include <semaphore.h>
# include "errors.h"

# define DEFAULT	-1
# define RED		"\x1B[31m"
# define GREEN		"\x1B[32m"
# define YELLOW		"\x1B[33m"
# define BLUE		"\x1B[36m"
# define ITALIC		"\x1B[3m"
# define RESET		"\x1B[0m"

typedef struct timeval	t_timeval;
typedef struct timezone	t_timezone;

enum
{
	TOOK_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	IS_DONE
};

typedef struct s_philos
{
	int				id;
	pid_t			process;
	int				his_fork;
	int				next_fork;
	int				n_of_meals;
	int				dead;
	unsigned long	next_meal;
	unsigned long	ate_at;
	struct s_philo	*philo;
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
	int	semaph_print;
	int	semaph_forks;
	int	semaph_wait;
}	t_alloc;

typedef struct s_philo
{
	t_philos		*philos;
	t_routine		routine;
	size_t			n_philos;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*wait;
	unsigned long	start;
	int				limited_meals;
	int				is_done;
	char			*exit_message;
	t_alloc			allocated;
}	t_philo;

/* ---------------- ERRORS ---------------- */
int				ft_error(t_philo *g, char *str);
int				ft_exit_error(t_philo *g, char *str, int usage);

/* ---------------- UTILS ---------------- */
void			ft_free_struct(t_philo *g);
unsigned long	ft_get_time(t_timezone *timezone);
void			ft_format(unsigned long timestamp, int id, char *log, int done);

/* ---------------- FUNCTIONS ---------------- */
size_t			ft_strlen(const char *s);
void			*ft_calloc(size_t count, size_t size);
int				ft_atoi(const char *str);

#endif