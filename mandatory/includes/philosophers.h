/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 03:04:46 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/21 14:00:09 by absalhi          ###   ########.fr       */
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

# define DEFAULT	-1
# define RED		"\x1B[31m"
# define GREEN		"\x1B[32m"
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
	int	mutex_print;
	int	mutex_eating;
	int	mutex_forks;
	int	mutex_wait;
}	t_alloc;

typedef struct s_philo
{
	t_philos		*philos;
	t_routine		routine;
	size_t			n_philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*wait;
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

/* ---------------- UTILS ---------------- */
void			*ft_routine_if_valid(void *philo);
int				ft_routine_if_done(t_philo *g, t_philos *philo);
void			*ft_routine(void *philo);
int				ft_take_forks(t_philo *g, t_philos *philo);
int				ft_eat(t_philo *g, t_philos *philo);
int				ft_sleep(t_philo *g, t_philos *philo);
void			ft_free_struct(t_philo *g);
int				ft_is_valid_timestamps(t_philo *g, char **argv);
int				ft_check_and_init(t_philo *g, int argc, char **argv);
int				ft_print_action(t_philo *g, t_philos *philo, int action);
int				ft_isint(char *str);
unsigned long	ft_get_time(t_timezone *timezone);
int				ft_init_struct(t_philo *g);

/* ---------------- FUNCTIONS ---------------- */
size_t			ft_strlen(const char *s);
void			*ft_calloc(size_t count, size_t size);
int				ft_atoi(const char *str);

#endif