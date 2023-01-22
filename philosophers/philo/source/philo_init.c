/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornhol <scornhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:38:06 by scornhol          #+#    #+#             */
/*   Updated: 2022/04/02 17:43:15 by scornhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief The major function of the initialization of the t_philo
 * 
 * @param philos the structure t_philo
 * @param argc argument count
 * @param argv argument vector
 * @return If successful 0 is returned, otherwise -1
 */
int	init_philos(t_philo **philos, int argc, char **argv)
{
	t_data	*data;
	t_philo	*tmp;
	int		i;

	if (init_data(&data, argc, argv) == -1)
		return (-1);
	if (pthread_mutex_init(&data->mutex_printf, NULL))
		return (put_error("pthread_mutex_init"));
	if (init_mutex_fork(data) == -1)
		return (-1);
	tmp = (t_philo *)malloc(sizeof(t_philo) * data->num_philos);
	if (!tmp)
		return (put_error("Failed to malloc philos"));
	i = -1;
	while (++i < data->num_philos)
		init_philo(tmp + i, i, data, data->mutex_fork);
	*philos = tmp;
	return (0);
}

/**
 * @brief The additional function of the initialization of the t_data.
 *  
 * @param data the structure t_data
 * @param argc argument count
 * @param argv argument vector
 * @return If successful 0 is returned, otherwise -1
 */
int	init_data(t_data **data, int argc, char **argv)
{
	t_data	*tmp;

	tmp = (t_data *)malloc(sizeof(t_data));
	if (!tmp)
		return (put_error("Failed to malloc data"));
	tmp->num_philos = set_argv(argv[1]);
	tmp->num_forks = tmp->num_philos;
	tmp->time_die = set_argv(argv[2]);
	tmp->time_eat = set_argv(argv[3]);
	tmp->time_sleep = set_argv(argv[4]);
	if (tmp->num_philos < 1 || tmp->num_philos > 200 || tmp->time_die == -1 || \
		tmp->time_sleep == -1 || tmp->time_eat == -1)
		return (put_error("Wrong arguments"));
	tmp->num_eat = -1;
	if (argc == 6)
	{
		tmp->num_eat = set_argv(argv[5]);
		if (tmp->num_eat == -1)
			return (put_error("Wrong arguments"));
	}
	tmp->stop = 0;
	*data = tmp;
	return (0);
}

/**
 * @brief mutex initialization for forks
 * 
 * @param data the structure t_data
 * @return If successful 0 is returned, otherwise -1
 */
int	init_mutex_fork(t_data *data)
{
	int	i;

	data->mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
						* data->num_forks);
	if (!data->mutex_fork)
		return (put_error("Failed to malloc mutex_fork"));
	i = -1;
	while (++i < data->num_forks)
	{
		if (pthread_mutex_init(data->mutex_fork + i, NULL))
			return (put_error("pthread_mutex_init mutex_fork"));
	}
	return (0);
}

/**
 * @brief The additional function of the initialization of the t_philo
 * 
 * @param philo the structure t_philo
 * @param i number
 * @param data the structure t_data
 * @param forks mutex_fork
 */
void	init_philo(t_philo *philo, int i, t_data *data, pthread_mutex_t *forks)
{
	philo->index = i + 1;
	philo->num_eat_count = 0;
	philo->time_meal = 0;
	philo->data = data;
	if (i == 0)
	{
		philo->left_fork = forks + data->num_philos - 1;
		philo->right_fork = forks + i;
	}
	else
	{
		philo->left_fork = forks + i - 1;
		philo->right_fork = forks + i;
	}
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
