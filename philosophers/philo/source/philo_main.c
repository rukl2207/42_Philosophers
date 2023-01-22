/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornhol <scornhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:18:22 by scornhol          #+#    #+#             */
/*   Updated: 2022/04/02 18:30:22 by scornhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief main
 * 
 * @param argc argument count
 * @param argv argument vector
 * @return If successful 0 is returned, otherwise -1
 */
int	main(int argc, char **argv)
{
	t_philo	*philos;

	if (argc < 5 || argc > 6)
	{
		put_help_message();
		return (put_error("Wrong number of argument"));
	}
	if (init_philos(&philos, argc, argv) == -1)
		return (-1);
	philos_start(philos);
	return (0);
}

/**
 * @brief running the basic logic. starts threads and monitors them
 * 
 * @param philos t_philo
 */
void	philos_start(t_philo *philos)
{
	int	i;

	i = -1;
	philos->data->time_start = get_time();
	while (++i < philos->data->num_philos)
	{
		(philos + i)->time_meal = get_time();
		if (pthread_create(&(philos + i)->pth_t, NULL, &start, philos + i))
			put_error("Failed to create the thread");
		pthread_detach((philos + i)->pth_t);
		usleep(50);
	}
	if (pthread_create(&philos->data->check_monitor, NULL, \
						&check_monitor, philos))
		put_error("Failed to create the thread");
	if (pthread_join(philos->data->check_monitor, NULL))
		put_error("Failed to join the thread");
	i = -1;
	while (++i < philos->data->num_forks)
		pthread_mutex_destroy(&philos->data->mutex_fork[i]);
	pthread_mutex_destroy(&philos->data->mutex_printf);
}

/**
 * @brief starting a separate thread for each philosopher
 * 
 * @param arg t_philo
 * @return void* 0
 */
void	*start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->stop)
	{
		philo_print(philo, "is thinking");
		pthread_mutex_lock(philo->left_fork);
		philo_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		philo_print(philo, "has taken a fork");
		philo_print(philo, "is eating");
		upgrade_sleep(philo->data->time_eat, philo->data);
		philo->time_meal = get_time();
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		if (!philo->data->stop)
			philo->num_eat_count += 1;
		philo_print(philo, "is sleeping");
		upgrade_sleep(philo->data->time_sleep, philo->data);
	}
	return (0);
}

/**
 * @brief print in stdout the message
 * 
 * @param philo t_philo
 * @param str message
 */
void	philo_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->mutex_printf);
	if (!philo->data->stop)
		printf("%lld %d %s\n", get_time() - philo->data->time_start, \
				philo->index, str);
	pthread_mutex_unlock(&philo->data->mutex_printf);
}

/**
 * @brief monitors exit conditions 
 * (death of a philosopher, everyone has eaten the specified number of times)
 * 
 * @param arg t_philo
 * @return void* 0
 */
void	*check_monitor(void *arg)
{
	t_philo	*philos;
	int		i;
	int		flag_all_eat;

	philos = (t_philo *)arg;
	while (!philos->data->stop)
	{
		i = -1;
		flag_all_eat = 0;
		while (++i < philos->data->num_philos)
		{
			if (get_time() - (philos + i)->time_meal > philos->data->time_die)
			{
				philo_print(philos + i, "died");
				philos->data->stop = 1;
				break ;
			}
			if (philos->data->num_eat != -1 && \
				(philos + i)->num_eat_count >= philos->data->num_eat)
				flag_all_eat++;
		}
		if (flag_all_eat == philos->data->num_philos)
			philos->data->stop = 1;
	}
	return (0);
}
