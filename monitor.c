/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:17:25 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/07/07 22:49:14 by mel-mouh         ###   ########.fr       */
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

bool	check_meals(t_philo *box)
{
	int		i;

	i = -1;
	while (++i < box->ph_nbr)
	{
		if (box->nte == -1 || box->eat_n[i] < box->nte)
			break ;
		if (i + 1 == box->ph_nbr)
			return (true);
	}
	return (false);
}

bool	check_starv(t_philo *box)
{
	int			i;
	long long	now;

	i = -1;
	now = start_timestamp();
	while (++i < box->ph_nbr)
	{
		if ((box->nte == -1 || box->eat_n[i] < box->nte)
			&& now - box->last_meal[i] > box->ttd)
		{
			printf("%lld %d died\n", now - box->f_time, i + 1);
			box->some_dead = true;
			return (true);
		}
		i++;
	}
	return (false);
}

void	*monitoring_routing(void *arg)
{
	t_philo		*box;

	box = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&box->death_lock);
		if (check_meals(box))
			break ;
		if (check_starv(box))
			break ;
		pthread_mutex_unlock(&box->death_lock);
		usleep(600);
	}
	pthread_mutex_unlock(&box->death_lock);
	return (NULL);
}
