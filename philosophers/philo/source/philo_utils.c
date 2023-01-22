/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornhol <scornhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:36:43 by scornhol          #+#    #+#             */
/*   Updated: 2022/04/02 17:03:12 by scornhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * Prints the message in case of an error and returns -1 as an error.
 * @param message error message
 * @return -1
 */
int	put_error(const char *message)
{
	printf("Error: %s\n", message);
	return (-1);
}

/**
 * displays a message about how to start the program correctly
 */
void	put_help_message(void)
{
	printf("| RULES FOR GETTING STARTED \t\t\t\t\t\t|\n"
		"| ./philo arg_1 arg_2 arg_3 agr_4 [arg_5] \t\t\t\t|\n"
		"|  arg_1, arg_2, arg_3, agr_4, [arg_5] - positive integer numbers	|\n"
		"|  arg_1 - number_of_philosophers, required argument \t\t\t|\n"
		"|  arg_2 - time_to_die, required argument \t\t\t\t|\n"
		"|  arg_3 - time_to_eat, required argument \t\t\t\t|\n"
		"|  arg_4 - time_to_sleep, required argument \t\t\t\t|\n"
		"|  arg_5 - number_of_times_each_philosopher_must_eat, additional\t|\n");
}

/**
 * get the time at the current moment
 * @return time in milliseconds
 */
long long	get_time(void)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	return (tm.tv_sec * 1000 + tm.tv_usec / 1000);
}

/**
 * upgarde time
 * @param time
 * @param data
 */
void	upgrade_sleep(long long time, t_data *data)
{
	long long	tm;

	tm = get_time();
	while (!data->stop)
	{
		if (get_time() - tm >= time)
			break ;
		usleep(500);
	}
}
