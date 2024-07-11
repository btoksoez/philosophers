/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btoksoez <btoksoez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:02:51 by btoksoez          #+#    #+#             */
/*   Updated: 2024/05/15 15:06:23 by btoksoez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <stdint.h>
# include <sys/types.h>

# define MAX_PHILOS 250

/*-------------------structs------------------*/
typedef struct s_table
{
	int						num_philos;
	size_t					time_to_die;
	size_t					time_to_eat;
	size_t					time_to_sleep;
	int						num_eat;
	pthread_mutex_t			die_lock;
	pthread_mutex_t			meal_lock;
	pthread_mutex_t			write_lock;
	struct s_philosopher	*philos;
	bool					philo_died;
}							t_table;

typedef struct s_philosopher
{
	pthread_t			thread;
	int					id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					num_eaten;
	pthread_mutex_t		*die_lock;
	pthread_mutex_t		*meal_lock;
	pthread_mutex_t		*write_lock;
	size_t				last_meal;
	size_t				start_time;
	bool				*dead;
	int					is_eating;
	t_table				*table;
}						t_philo;

/*--------------------init--------------------*/
void	init_forks(pthread_mutex_t *forks, t_table *table);
void	init_table(char *argv[], int argc, t_table *table);
void	init_philos(t_philo *philos, t_table *table, pthread_mutex_t *forks);

/*-------------------parsing------------------*/
bool	parse_args(int argc, char *argv[]);
bool	check_args(int argc, char *argv[]);

/*-------------------simulation----------------*/
void	philo_eat(t_philo *philo, t_table *table);
void	philo_sleep(t_philo *philo, t_table *table);
void	philo_think(t_philo *philo);
void	*philo_behaviour(void *arg);
void	start_simulation(t_table *table);

/*-------------------monitor-------------------*/
bool	is_dead(t_philo *philo);
bool	all_philos_ate(t_table *table);
void	*observer_behaviour(void *arg);
bool	check_if_dead(t_table *table);

/*--------------------main---------------------*/
void	clean_up(t_table *table, pthread_mutex_t *forks);
void	one_philo(t_philo *philo);

/*--------------------utils--------------------*/
long	get_time(void);
int		ft_atoi(char *str);
void	print_message(char *message, t_philo *philo);
int		ft_usleep(size_t milliseconds, t_philo *philo);
void	choose_forks(t_philo *p, pthread_mutex_t **ff, pthread_mutex_t **sf);

#endif
