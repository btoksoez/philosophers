/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btoksoez <btoksoez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:24:29 by btoksoez          #+#    #+#             */
/*   Updated: 2024/05/15 14:56:22 by btoksoez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_forks(pthread_mutex_t *forks, t_table *table)
{
	int				i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_philos(t_philo *philos, t_table *table, pthread_mutex_t *forks)
{
	int				i;

	i = 0;
	while (i < table->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = &forks[i];
		if (i == 0)
			philos[i].right_fork = &forks[table->num_philos - 1];
		else
			philos[i].right_fork = &forks[i - 1];
		philos[i].num_eaten = 0;
		philos[i].meal_lock = &table->meal_lock;
		philos[i].die_lock = &table->die_lock;
		philos[i].write_lock = &table->write_lock;
		philos[i].last_meal = get_time();
		philos[i].start_time = get_time();
		philos[i].dead = &table->philo_died;
		philos[i].is_eating = 0;
		philos[i].table = table;
		i++;
	}
	table->philos = philos;
}

void	init_table(char *argv[], int argc, t_table *table)
{
	table->num_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->num_eat = ft_atoi(argv[5]);
	else
		table->num_eat = -1;
	pthread_mutex_init(&table->die_lock, NULL);
	pthread_mutex_init(&table->meal_lock, NULL);
	pthread_mutex_init(&table->write_lock, NULL);
	table->philos = NULL;
	table->philo_died = 0;
}
