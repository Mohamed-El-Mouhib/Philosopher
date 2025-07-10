/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:17:25 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/07/09 19:17:22 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitoring_states(t_data *box, char *str)
{
	pthread_mutex_lock(&box->ptr->death_lock);
	if (!box->ptr->some_dead)
		printf("%lld %d %s\n", start_timestamp()
			- box->ptr->f_time, box->ind, str);
	pthread_mutex_unlock(&box->ptr->death_lock);
}

void	soft_sleeping(long long duration, t_data *box)
{
	long	start;
	long	now;

	start = start_timestamp();
	while (1)
	{
		pthread_mutex_lock(&box->ptr->death_lock);
		if (box->ptr->some_dead)
		{
			pthread_mutex_unlock(&box->ptr->death_lock);
			return ;
		}
		pthread_mutex_unlock(&box->ptr->death_lock);
		now = start_timestamp();
		if (now - start >= duration)
			break ;
		usleep(400);
	}
}

bool	check_meals(t_philo *box)
{
	int		i;

	i = -1;
	if (box->nte == -1)
		return (false);
	pthread_mutex_lock(&box->meal_update);
	while (++i < box->ph_nbr)
	{
		if (box->eat_n[i] < box->nte)
			return ((void)pthread_mutex_unlock(&box->meal_update), false);
	}
	pthread_mutex_unlock(&box->meal_update);
	return (true);
}

bool	check_starv(t_philo *box)
{
	int			i;

	i = -1;
	while (++i < box->ph_nbr)
	{
		pthread_mutex_lock(&box->death_lock);
		pthread_mutex_lock(&box->meal_update);
		if ((box->nte == -1 || box->eat_n[i] < box->nte)
			&& start_timestamp() - box->last_meal[i] > box->ttd)
		{
			printf("%lld %d died\n", start_timestamp() - box->f_time, i + 1);
			pthread_mutex_unlock(&box->meal_update);
			box->some_dead = true;
			return ((void)pthread_mutex_unlock(&box->death_lock), true);
		}
		i++;
		pthread_mutex_unlock(&box->meal_update);
		pthread_mutex_unlock(&box->death_lock);
	}
	return (false);
}

void	*monitoring_routing(void *arg)
{
	t_philo		*box;

	box = (t_philo *)arg;
	while (1)
	{
		if (check_meals(box) || check_starv(box))
			break ;
		usleep(400);
	}
	return (NULL);
}
