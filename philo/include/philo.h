/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 18:02:42 by rmamzer           #+#    #+#             */
/*   Updated: 2025/12/27 18:20:47 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <limits.h>
# include <sys/time.h>

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
# define ERROR_MTX_INIT "Error: mutex initialization failure\n"





typedef struct s_philo
{
	int	id;
	int	meals_eaten;
	size_t last_meal_time;
	pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;
	pthread_t thread;
}	t_philo;

typedef enum e_action
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN
}	t_action;


typedef struct s_academy
{
	int philos_total;
	size_t time_to_die;
	size_t time_to_sleep;
	size_t time_to_eat;
	size_t time_start;
	int num_of_meals;

	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mtx_msg;
// 	pthread_mutex_t mtx_portion;
// 	pthread_mutex_t mtx_death;


} t_academy;


#endif