/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 18:02:30 by rmamzer           #+#    #+#             */
/*   Updated: 2025/12/25 19:40:55 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}


bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}



void write_error_msg(char *msg)
{
	write (STDERR_FILENO, msg, ft_strlen(msg));
}



bool check_arg_num(int argc)
{
	if (argc !=5 && argc !=6)
		return(FAILURE);
	return (SUCCESS);

}

bool check_input(int argc, char **argv)
{
	int i;
	int j;

	if (check_arg_num(argc)== FAILURE)
		return (write_error_msg(ERROR_ARGSN),FAILURE);
	i = 0;
	while(argv[++i])
	{
		j=0;
		while (argv[i][j] && ft_isspace(argv[i][j]))
			j++;
		if (argv[i][j] == '\0')
			return(write_error_msg(ERROR_ARGEMPTY), FAILURE);
		while (argv[i][j] && ft_isdigit(argv[i][j]))
			j++;
		if (argv[i][j] != '\0')
			return (write_error_msg(ERROR_ARG), FAILURE);
	}
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	if (check_input(argc, argv) == FAILURE)
		return(FAILURE);
	return (SUCCESS);
}