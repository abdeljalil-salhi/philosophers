/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 09:14:51 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/23 16:29:34 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_ARGS_ARGC_INVALID "Invalid number of arguments."
# define ERR_ARGS_NUMBER_INVALID "One of the arguments isn't a valid number."
# define ERR_ARGS_NUMBER_MINIMUM "The durations must be greater than 60ms."
# define ERR_ARGS_MEALS_MINIMUM "The number of meals must be greater than one."
# define ERR_ARGS_PHILO_MINIMUM "You need at least one philosopher to start."

# define ERR_TIME "Error while getting the time of the system."
# define ERR_SLEEP "Error while system sleeping."

# define ERR_PHILO_MALLOC "Error allocating the philosophers."
# define ERR_PHILO_THREAD_CREAT "Error while creating the philos threads."
# define ERR_PHILO_THREAD_DETACH "Error while detaching the philos threads."

# define ERR_CHECK_THREAD_CREAT "Error while creating the check thread."
# define ERR_CHECK_THREAD_DETACH "Error while detaching the check thread."

# define ERR_FORK_MUTEX_MALLOC "Error allocating the forks mutexes."
# define ERR_FORK_MUTEX_INIT "Error initializing the forks mutex."
# define ERR_FORK_MUTEX_LOCK "Error while locking the fork mutex."
# define ERR_FORK_MUTEX_UNLOCK "Error while unlocking the fork mutex."
# define ERR_FORK_MUTEX_DESTROY "Error while destroying the forks mutexes."

# define ERR_EATING_MUTEX_MALLOC "Error allocating the eating mutex."
# define ERR_EATING_MUTEX_INIT "Error initializing the eating mutex."
# define ERR_EATING_MUTEX_LOCK "Error while locking the eating mutex."
# define ERR_EATING_MUTEX_UNLOCK "Error while unlocking the eating mutex."
# define ERR_EATING_MUTEX_DESTROY "Error while destroying the eating mutex."

# define ERR_PHILO_MUTEX_MALLOC "Error while allocating a philo mutex."
# define ERR_PHILO_MUTEX_INIT "Error while initializing a philo mutex."
# define ERR_PHILO_MUTEX_LOCK "Error while locking a philo mutex."
# define ERR_PHILO_MUTEX_UNLOCK "Error while unlocking a philo mutex."
# define ERR_PHILO_MUTEX_DESTROY "Error while destroying a philo mutex."

# define ERR_DONE_MUTEX_MALLOC "Error allocating the is_done mutex."
# define ERR_DONE_MUTEX_INIT "Error initializing the is_done mutex."
# define ERR_DONE_MUTEX_LOCK "Error while locking the is_done mutex."
# define ERR_DONE_MUTEX_UNLOCK "Error while unlocking the is_done mutex."
# define ERR_DONE_MUTEX_DESTROY "Error while destroying the is_done mutex."

# define ERR_EXIT_MUTEX_MALLOC "Error allocating the exit error mutex."
# define ERR_EXIT_MUTEX_INIT "Error initializing the exit error mutex."
# define ERR_EXIT_MUTEX_LOCK "Error while locking the exit error mutex."
# define ERR_EXIT_MUTEX_UNLOCK "Error while unlocking the exit error mutex."
# define ERR_EXIT_MUTEX_DESTROY "Error while destroying the exit error mutex."

# define ERR_PRINT_MUTEX_MALLOC "Error allocating the print mutex."
# define ERR_PRINT_MUTEX_INIT "Error initializing the print mutex."
# define ERR_PRINT_MUTEX_LOCK "Error while locking the print mutex."
# define ERR_PRINT_MUTEX_UNLOCK "Error while unlocking the print mutex."
# define ERR_PRINT_MUTEX_DESTROY "Error while destroying the print mutex."

# define ERR_WAIT_MUTEX_MALLOC "Error allocating the wait mutex."
# define ERR_WAIT_MUTEX_INIT "Error initializing the wait mutex."
# define ERR_WAIT_MUTEX_LOCK "Error while locking the wait mutex."
# define ERR_WAIT_MUTEX_UNLOCK "Error while unlocking the wait mutex."
# define ERR_WAIT_MUTEX_DESTROY "Error while destroying the wait mutex."

#endif