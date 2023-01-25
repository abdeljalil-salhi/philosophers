/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 03:04:46 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/25 06:35:23 by absalhi          ###   ########.fr       */
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
# include "errors.h"

# define DEFAULT	-1
# define NONULL		"no-null"
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
	pthread_t		thread;
	int				his_fork;
	int				next_fork;
	int				n_of_meals;
	int				dead;
	unsigned long	next_meal;
	unsigned long	ate_at;
	pthread_mutex_t	*eating;
	pthread_mutex_t	*next_meal_mutex;
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
	int	mutex_eating;
	int	mutex_next_meal;
	int	mutex_forks;
	int	mutex_print;
	int	mutex_wait;
	int	mutex_is_done;
	int	mutex_exit;
}	t_alloc;

typedef struct s_philo
{
	t_philos		*philos;
	t_routine		routine;
	size_t			n_philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*wait;
	pthread_mutex_t	*is_done_mutex;
	pthread_mutex_t	*exit_mutex;
	unsigned long	start;
	int				limited_meals;
	int				is_done;
	char			*exit_message;
	t_alloc			allocated;
}	t_philo;

/* ------------ FUNCTIONS SPECIFIC ------------ */
typedef struct s_sroutine
{
	t_philos		*casted;
	unsigned long	_time;
	pthread_t		check;
}	t_sroutine;

/* ---------------- ERRORS ---------------- */
int				ft_error(t_philo *g, char *str);
void			*ft_perror(t_philo *g, char *str);
int				ft_exit_error(t_philo *g, char *str, int usage);

/* ---------------- INIT ---------------- */
int				ft_init_struct(t_philo *g);
int				ft_init_mutexes(t_philo *g);
int				ft_init_mutex_locks(t_philo *g);
int				ft_init_philo(t_philo *g, int id);

/* ---------------- UTILS ---------------- */
void			*ft_routine_if_valid(void *philo);
int				ft_routine_invalid(t_philo *g, t_philos *philo);
int				ft_routine_if_done(t_philo *g, t_philos *philo);
void			*ft_routine(void *philo);
int				ft_repetitive_routine(t_philo *g, t_philos *philo);
int				ft_take_forks(t_philo *g, t_philos *philo);
int				ft_eat(t_philo *g, t_philos *philo);
int				ft_sleep(t_philo *g, t_philos *philo);
void			ft_destroy_mutex(t_philo *g, pthread_mutex_t *mutex, char *err);
void			ft_free_mutexes(t_philo *g);
void			ft_free_struct(t_philo *g);
int				ft_is_valid_timestamps(t_philo *g, char **argv);
int				ft_check_and_init(t_philo *g, int argc, char **argv);
int				ft_print_action(t_philo *g, t_philos *philo, int action);
int				ft_isint(char *str);
unsigned long	ft_get_time(t_timezone *timezone);
int				ft_safe_read_is_done(t_philo *g);
int				ft_usleep(t_philo *g, unsigned long _time);
void			ft_format(unsigned long timestamp, int id, char *log, int done);
int				ft_safe_read_is_done(t_philo *g);
char			*ft_safe_read_exit_message(t_philo *g);

/* ---------------- FUNCTIONS ---------------- */
size_t			ft_strlen(const char *s);
void			*ft_calloc(size_t count, size_t size);
int				ft_atoi(const char *str);

#endif