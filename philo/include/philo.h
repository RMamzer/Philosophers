/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 18:02:42 by rmamzer           #+#    #+#             */
/*   Updated: 2025/12/26 19:54:08 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <limits.h>

# define SUCCESS 0
# define FAILURE 1

# define ERROR_ARGSN "Wrong number of arguments\nUsage: [number_of_philosophers]\
 [time_to_die] [time_to_eat] [time_to_sleep] (optional\
[number_of_times_each_philosopher_must_eat])\n"
# define ERROR_ARGEMPTY "Error: empty argument\n"
# define ERROR_ARG "Error: non-digit input\n"
# define ERROR_INTOVRF "Error: number is too large\n"
# define ERROR_ARGZERO "Error: number cannot be 0\n"
# define ERROR_MEM "Error: memory allocation failure\n"


typedef struct s_philo
{
	int id;
} t_philo;




typedef struct s_academy
{
	int philos_total;
	int time_to_die;
	int time_to_sleep;
	int time_to_eat;
	int num_of_meals;

	t_philo			*philo;
	pthread_mutex_t	*fork;

} t_academy;


#endif