/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btoksoez <btoksoez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:35:27 by btoksoez          #+#    #+#             */
/*   Updated: 2024/05/17 13:06:45 by btoksoez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_eat(t_philo *philo, t_table *table)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	choose_forks(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	print_message("has taken a fork", philo);
	ft_usleep(1, philo);
	pthread_mutex_lock(second_fork);
	print_message("has taken a fork", philo);
	philo->is_eating = 1;
	print_message("is eating", philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->num_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(table->time_to_eat, philo);
	philo->is_eating = 0;
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}

void	philo_sleep(t_philo *philo, t_table *table)
{
	print_message("is sleeping", philo);
	ft_usleep(table->time_to_sleep, philo);
}

void	philo_think(t_philo *philo)
{
	print_message("is thinking", philo);
}

void	*philo_behaviour(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->num_philos == 1)
		return (one_philo(philo), NULL);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_dead(philo))
	{
		philo_eat(philo, philo->table);
		philo_sleep(philo, philo->table);
		philo_think(philo);
	}
	return (NULL);
}

void	start_simulation(t_table *table)
{
	int			i;
	pthread_t	observer;

	pthread_create(&observer, NULL, &observer_behaviour, table);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_create(&table->philos[i].thread, NULL,
			&philo_behaviour, &table->philos[i]);
		i++;
	}
	pthread_join(observer, NULL);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}
