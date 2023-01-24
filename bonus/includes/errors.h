/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:36:59 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/24 02:05:45 by absalhi          ###   ########.fr       */
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
# define ERR_PHILO_PROCESS_FORK "Error while forking the philos processes."

# define ERR_PRINT_SEMAPH_OPEN "Error while opening print semaphore."
# define ERR_PRINT_SEMAPH_WAIT "Error while waiting print semaphore."
# define ERR_PRINT_SEMAPH_POST "Error while posting print semaphore."
# define ERR_PRINT_SEMAPH_UNLINK "Error while unlinking print semaphore."
# define ERR_PRINT_SEMAPH_CLOSE "Error while closing print semaphore."

# define ERR_WAIT_SEMAPH_OPEN "Error while opening wait semaphore."
# define ERR_WAIT_SEMAPH_WAIT "Error while waiting wait semaphore."
# define ERR_WAIT_SEMAPH_POST "Error while posting wait semaphore."
# define ERR_WAIT_SEMAPH_UNLINK "Error while unlinking wait semaphore."
# define ERR_WAIT_SEMAPH_CLOSE "Error while closing wait semaphore."

# define ERR_FORKS_SEMAPH_OPEN "Error while opening forks semaphore."
# define ERR_FORKS_SEMAPH_WAIT "Error while waiting forks semaphore."
# define ERR_FORKS_SEMAPH_POST "Error while posting forks semaphore."
# define ERR_FORKS_SEMAPH_UNLINK "Error while unlinking forks semaphore."
# define ERR_FORKS_SEMAPH_CLOSE "Error while closing forks semaphore."

# define ERR_CHECK_SEMAPH_OPEN "Error while opening check semaphore."
# define ERR_CHECK_SEMAPH_WAIT "Error while waiting check semaphore."
# define ERR_CHECK_SEMAPH_POST "Error while posting check semaphore."
# define ERR_CHECK_SEMAPH_UNLINK "Error while unlinking check semaphore."
# define ERR_CHECK_SEMAPH_CLOSE "Error while closing check semaphore."

# define ERR_MEALS_SEMAPH_OPEN "Error while opening meals semaphore."
# define ERR_MEALS_SEMAPH_WAIT "Error while waiting meals semaphore."
# define ERR_MEALS_SEMAPH_POST "Error while posting meals semaphore."
# define ERR_MEALS_SEMAPH_UNLINK "Error while unlinking meals semaphore."
# define ERR_MEALS_SEMAPH_CLOSE "Error while closing meals semaphore."

#endif
