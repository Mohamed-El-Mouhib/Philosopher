/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:17:25 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/07/04 23:14:37 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitoring_states(t_data *box, char *str)
{
	long long	now;

	now = start_timestamp();
	pthread_mutex_lock(&box->ptr->death_lock);
	if (!box->ptr->some_dead)
		printf("%lld %d %s\n", now - box->ptr->f_time, box->ind, str);
	pthread_mutex_unlock(&box->ptr->death_lock);
}

void	soft_sleeping(long long duration)
{
	long	start;
	long	now;

	start = start_timestamp();
	while (1)
	{
		now = start_timestamp();
		if (now - start >= duration)
			break ;
		usleep(600);
	}
}

void	*monitoring_routing(void *arg)
{
	int			i;
	t_philo		*box;
	long long	now;

	box = (t_philo *)arg;
	while (1)
	{
		i = -1;
		while (++i < box->ph_nbr)
		{
			pthread_mutex_lock(&box->death_lock);
			now = start_timestamp();
			if ((now - box->last_meal[i] > box->ttd)
				|| (box->nte >= 0 && box->nte == box->eat_n[i]))
			{
				printf("%lld %d is died\n", now - box->f_time, i + 1);
				box->some_dead = true;
				pthread_mutex_unlock(&box->death_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&box->death_lock);
		}
		usleep(500);
	}
	return (NULL);
}
