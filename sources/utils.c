/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btoksoez <btoksoez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:10:19 by btoksoez          #+#    #+#             */
/*   Updated: 2024/05/17 12:47:53 by btoksoez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	if (!str)
		return (0);
	while (str[i] >= ' ' && str[i] <= '\r')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_message(char *message, t_philo *philo)
{
	size_t	time_ms;

	pthread_mutex_lock(philo->write_lock);
	time_ms = get_time() - philo->start_time;
	if (!is_dead(philo))
		printf("%zu %d %s\n", time_ms, philo->id, message);
	pthread_mutex_unlock(philo->write_lock);
}

int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds && !is_dead(philo))
		usleep(500);
	return (0);
}

void	choose_forks(t_philo *p, pthread_mutex_t **ff, pthread_mutex_t **sf)
{
	if (p->id % 2 == 0)
	{
		*ff = p->left_fork;
		*sf = p->right_fork;
	}
	else
	{
		*ff = p->right_fork;
		*sf = p->left_fork;
	}
}
