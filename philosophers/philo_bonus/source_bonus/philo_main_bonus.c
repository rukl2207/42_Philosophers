/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornhol <scornhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 20:57:14 by scornhol          #+#    #+#             */
/*   Updated: 2022/04/02 18:32:01 by scornhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

/**
 * @brief main
 * 
 * @param argc argument count
 * @param argv argument vector
 * @return If successful 0 is returned, otherwise -1
 */
int	main(int argc, char **argv)
{
	t_philo	*philo;
	int		i;

	if (argc < 5 || argc > 6)
	{
		put_help_message();
		put_error("Wrong number of argument");
	}
	philo = init_philo(argc, argv);
	i = -1;
	philo->time_start = get_time();
	while (++i < philo->num_philos)
	{
		philo->pid[i] = fork();
		if (philo->pid[i] == -1)
			put_error("Failed to crete fork");
		if (philo->pid[i] == 0)
		{
			philo->index = i + 1;
			philo->time_meal = get_time();
			philo_start(philo);
		}
	}
	philo_exit(&philo);
	return (0);
}

/**
 * @brief starting a separate process for each philosopher
 * 
 * @param philo t_philo
 */
void	philo_start(t_philo *philo)
{
	if (pthread_create(&philo->check_monitor, NULL, &check_monitor, philo))
		put_error("Failed to create the thread");
	if (philo->index % 2 == 1)
		usleep(1000);
	while (1)
	{
		philo_print(philo, "is thinking");
		sem_wait(philo->block_fork);
		philo_print(philo, "has taken a fork");
		sem_wait(philo->block_fork);
		philo_print(philo, "has taken a fork");
		philo_print(philo, "is eating");
		upgrade_sleep(philo->time_eat, philo);
		philo->time_meal = get_time();
		sem_post(philo->block_fork);
		sem_post(philo->block_fork);
		philo->num_eat_count += 1;
		philo_print(philo, "is sleeping");
		upgrade_sleep(philo->time_sleep, philo);
	}
	if (pthread_join(philo->check_monitor, NULL))
		put_error("Failed to join the thread");
}

/**
 * @brief monitors exit conditions 
 * (death of a philosopher, everyone has eaten the specified number of times)
 * 
 * @param arg t_philo
 */
void	*check_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->stop)
	{
		usleep(100);
		if (get_time() - philo->time_meal > philo->time_die)
		{
			philo->died = 1;
			sem_wait(philo->block_printf);
			printf("%lld %d %s\n", get_time() - philo->time_start, \
					philo->index, "died");
			philo->stop = 1;
			break ;
		}
		if (philo->num_eat != -1 && philo->num_eat_count >= philo->num_eat)
		{
			philo->stop = 1;
			break ;
		}
	}
	if (philo->died)
		exit(EXIT_FAILURE);
	else
		exit (EXIT_SUCCESS);
}

/**
 * @brief print in stdout the message
 * 
 * @param philo t_philo
 * @param str message
 */
void	philo_print(t_philo *philo, char *str)
{
	sem_wait(philo->block_printf);
	if (!philo->stop)
		printf("%lld %d %s\n", get_time() - philo->time_start, \
				philo->index, str);
	sem_post(philo->block_printf);
}

/**
 * @brief freeing allocated memory, closing semaphores, kill processes 
 * before exiting
 * 
 * @param philo t_philo
 */
void	philo_exit(t_philo **philo)
{
	t_philo	*tmp;
	int		i;
	int		status;

	tmp = *philo;
	i = 0;
	while (i < tmp->num_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < tmp->num_philos)
				kill(tmp->pid[i], SIGKILL);
			break ;
		}
		i++;
	}
	sem_close(tmp->block_printf);
	sem_close(tmp->block_fork);
	sem_unlink("/block_print");
	sem_unlink ("/block_forks");
	free(tmp->pid);
	free(tmp);
}
