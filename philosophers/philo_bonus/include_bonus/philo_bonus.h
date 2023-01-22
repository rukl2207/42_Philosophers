/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornhol <scornhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 20:56:31 by scornhol          #+#    #+#             */
/*   Updated: 2022/04/02 14:31:01 by scornhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornhol <scornhol@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:16:39 by scornhol          #+#    #+#             */
/*   Updated: 2022/03/31 23:25:24 by scornhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_philo
{
	int				num_philos;
	int				num_forks;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_eat;
	int				num_eat_count;
	int				stop;
	int				died;
	int				*pid;
	sem_t			*block_printf;
	sem_t			*block_fork;
	long long int	time_start;
	int				index;
	long long int	time_meal;
	pthread_t		check_monitor;
}	t_philo;

// philo_main_bonus.c
int			main(int argc, char **argv);
void		philo_start(t_philo *philo);
void		*check_monitor(void *arg);
void		philo_print(t_philo *philo, char *str);
void		philo_exit(t_philo **philo);

// philo_init_bonus.c
t_philo		*init_philo(int argc, char **argv);
t_philo		*init_data(int argc, char **argv);
int			set_argv(const char *str);

// philo_utils_bonus.c
int			put_error(const char *message);
void		put_help_message(void);
long long	get_time(void);
void		upgrade_sleep(long long time, t_philo *philo);

#endif