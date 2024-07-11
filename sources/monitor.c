/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btoksoez <btoksoez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:39:04 by btoksoez          #+#    #+#             */
/*   Updated: 2024/05/17 13:35:33 by btoksoez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	all_philos_ate(t_table *table)
{
	int				i;
	int				finished_eating;
	t_philo			*philos;

	i = 0;
	finished_eating = 0;
	philos = table->philos;
	if (table->num_eat == -1)
		return (false);
	while (i < table->num_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].num_eaten >= table->num_eat)
			finished_eating++;
		pthread_mutex_unlock(&table->meal_lock);
		i++;
	}
	if (finished_eating == table->num_philos)
	{
		pthread_mutex_lock(&table->die_lock);
		*philos->dead = 1;
		return (pthread_mutex_unlock(&table->die_lock), true);
	}
	return (false);
}

void	*observer_behaviour(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (check_if_dead(table) || all_philos_ate(table))
			break ;
	}
	return (arg);
}

bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->die_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->die_lock);
		return (true);
	}
	pthread_mutex_unlock(philo->die_lock);
	return (false);
}

bool	philo_dead(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_time() - philo->last_meal >= table->time_to_die
		&& philo->is_eating == 0 && philo->num_eaten != table->num_eat)
		return (pthread_mutex_unlock(philo->meal_lock), true);
	pthread_mutex_unlock(philo->meal_lock);
	return (false);
}

bool	check_if_dead(t_table *table)
{
	int				i;
	t_philo			*philos;

	i = 0;
	philos = table->philos;
	while (i < table->num_philos)
	{
		if (philo_dead(table, &philos[i]))
		{
			print_message("died", &philos[i]);
			pthread_mutex_lock(&table->die_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(&table->die_lock);
			return (true);
		}
		i++;
	}
	return (false);
}
