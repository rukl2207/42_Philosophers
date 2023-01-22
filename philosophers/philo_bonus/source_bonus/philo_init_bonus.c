/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornhol <scornhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 20:57:46 by scornhol          #+#    #+#             */
/*   Updated: 2022/04/02 17:46:26 by scornhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

/**
 * @brief The major function of the initialization of the t_philo
 * 
 * @param argc argument count
 * @param argv argument vector
 * @return the structure t_philo
 */
t_philo	*init_philo(int argc, char **argv)
{
	t_philo	*tmp;

	tmp = init_data(argc, argv);
	tmp->pid = (int *)malloc(sizeof(int) * tmp->num_forks);
	if (!tmp->pid)
		put_error("Failed to malloc for pid in init_philo");
	sem_unlink("/block_print");
	sem_unlink("/block_forks");
	tmp->block_printf = sem_open("/block_print", O_CREAT, 0644, 1);
	tmp->block_fork = sem_open("/block_forks", O_CREAT, 0644, tmp->num_forks);
	if (tmp->block_printf <= 0 || tmp->block_fork <= 0)
		put_error("Failed to open semaphore");
	return (tmp);
}

/**
 * @brief The additional function of the initialization of the t_philo.
 * 
 * @param argc argument count
 * @param argv argument vector
 * @return the structure t_philo
 */
t_philo	*init_data(int argc, char **argv)
{
	t_philo	*tmp;

	tmp = (t_philo *)malloc(sizeof(t_philo));
	if (!tmp)
		put_error("Failed to malloc philo");
	tmp->num_philos = set_argv(argv[1]);
	tmp->num_forks = tmp->num_philos;
	tmp->time_die = set_argv(argv[2]);
	tmp->time_eat = set_argv(argv[3]);
	tmp->time_sleep = set_argv(argv[4]);
	if (tmp->num_philos < 1 || tmp->num_philos > 200 || tmp->time_die == -1 || \
		tmp->time_sleep == -1 || tmp->time_eat == -1)
		put_error("Wrong arguments");
	tmp->num_eat = -1;
	if (argc == 6)
	{
		tmp->num_eat = set_argv(argv[5]);
		if (tmp->num_eat == -1)
			put_error("Wrong arguments");
	}
	tmp->num_eat_count = 0;
	tmp->stop = 0;
	tmp->died = 0;
	return (tmp);
}

/**
 * @brief Checks and sets the argument in the structure
 * 
 * @param str argument
 * @return possitive integer number
 */
int	set_argv(const char *str)
{
	long int	num;

	while (*str == ' ' || *str == '\f' || *str == '\n' || \
			*str == '\r' || *str == '\t' || *str == '\v')
		str++;
	num = 0;
	if (*str == '-')
		return (-1);
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - '0';
		if (num > 2147483647)
			return (-1);
		str++;
	}
	if (*str != '\0')
		return (-1);
	return ((int)num);
}
