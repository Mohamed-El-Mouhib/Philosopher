/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:54:22 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/07/06 16:04:26 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_loop(int left, int right, t_data *box)
{
	pthread_mutex_lock(&box->ptr->death_lock);
	while (!box->ptr->some_dead
		&& (box->ptr->nte == -1
			|| box->ptr->eat_n[box->ind - 1] < box->ptr->nte))
	{
		pthread_mutex_unlock(&box->ptr->death_lock);
		pthread_mutex_lock(&box->ptr->forks[left]);
		monitoring_states(box, "is taking fork");
		pthread_mutex_lock(&box->ptr->forks[right]);
		monitoring_states(box, "is taking fork");
		pthread_mutex_lock(&box->ptr->death_lock);
		box->ptr->eat_n[box->ind - 1] += 1;
		box->ptr->last_meal[box->ind - 1] = start_timestamp();
		pthread_mutex_unlock(&box->ptr->death_lock);
		monitoring_states(box, "is eating");
		soft_sleeping(box->ptr->tte);
		monitoring_states(box, "is sleeping");
		pthread_mutex_unlock(&box->ptr->forks[left]);
		pthread_mutex_unlock(&box->ptr->forks[right]);
		soft_sleeping(box->ptr->tts);
		monitoring_states(box, "is thinking");
		pthread_mutex_lock(&box->ptr->death_lock);
	}
}

void	*thread_preparing(void *arg)
{
	t_data	*box;
	int		left;
	int		right;

	box = (t_data *)arg;
	right = box->ind - 1;
	left = box->ind;
	if (box->ind == box->ptr->ph_nbr)
		left = 0;
	if (box->ind % 2 == 0)
		usleep(300);
	if (box->ptr->ph_nbr == 1)
	{
		printf("%lld %d is taking a fork\n",
			start_timestamp() - box->ptr->f_time, box->ind);
	}
	else
	{
		philo_loop(left, right, box);
		pthread_mutex_unlock(&box->ptr->death_lock);
	}
	return (NULL);
}
