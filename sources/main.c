/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btoksoez <btoksoez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:01:36 by btoksoez          #+#    #+#             */
/*   Updated: 2024/05/15 15:06:15 by btoksoez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	one_philo(t_philo *philo)
{
	print_message("has taken a fork", philo);
	ft_usleep(philo->table->time_to_die, philo);
}

void	clean_up(t_table *table, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->die_lock);
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->write_lock);
}

int	main(int argc, char *argv[])
{
	t_table			table;
	t_philo			philos[MAX_PHILOS];
	pthread_mutex_t	forks[MAX_PHILOS];

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat>\
<time_to_sleep> [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	if (!parse_args(argc, argv))
		return (1);
	init_table(argv, argc, &table);
	init_forks(forks, &table);
	init_philos(philos, &table, forks);
	start_simulation(&table);
	clean_up(&table, forks);
}
