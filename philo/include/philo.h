/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 18:02:42 by rmamzer           #+#    #+#             */
/*   Updated: 2025/12/25 19:45:57 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

# define SUCCESS 0
# define FAILURE 1

#define ERROR_ARGSN "Wrong number of arguments\nUsage: [number_of_philosophers]\
 [time_to_die] [time_to_eat] [time_to_sleep] (optional\
[number_of_times_each_philosopher_must_eat])\n"
#define ERROR_ARGEMPTY "Error: empty argument\n"
#define ERROR_ARG "Error: only digits allowed\n"


#endif