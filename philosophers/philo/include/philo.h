/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornhol <scornhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:16:39 by scornhol          #+#    #+#             */
/*   Updated: 2022/04/02 11:19:11 by scornhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				num_philos;
	int				num_forks;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_eat;
	int				stop;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_printf;
	long long int	time_start;
	pthread_t		check_monitor;
}	t_data;

typedef struct s_philo
{
	int				index;
	int				num_eat_count;
	long long int	time_meal;
	t_data			*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		pth_t;
}	t_philo;

// philo_main.c
int			main(int argc, char **argv);
void		philos_start(t_philo *philos);
void		*start(void *arg);
void		philo_print(t_philo *philo, char *str);
void		*check_monitor(void *arg);

// philo_init.c
int			init_philos(t_philo **philos, int argc, char **argv);
int			init_data(t_data **data, int argc, char **argv);
int			init_mutex_fork(t_data *data);
void		init_philo(t_philo *philo, int i, t_data *data, \
						pthread_mutex_t *forks);
int			set_argv(const char *str);

// philo_utils.c
int			put_error(const char *message);
void		put_help_message(void);
long long	get_time(void);
void		upgrade_sleep(long long time, t_data *data);

#endif