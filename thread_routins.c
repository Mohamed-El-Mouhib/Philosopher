/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:54:22 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/07/07 22:31:34 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_loop(t_data *box)
{
	pthread_mutex_lock(&box->ptr->death_lock);
	while (!box->ptr->some_dead
		&& (box->ptr->nte == -1
			|| box->ptr->eat_n[box->ind - 1] < box->ptr->nte))
	{
		pthread_mutex_unlock(&box->ptr->death_lock);
		pthread_mutex_lock(&box->ptr->forks[box->l]);
		monitoring_states(box, " has taken a fork");
		pthread_mutex_lock(&box->ptr->forks[box->r]);
		monitoring_states(box, " has taken a fork");
		pthread_mutex_lock(&box->ptr->death_lock);
		box->ptr->eat_n[box->ind - 1] += 1;
		box->ptr->last_meal[box->ind - 1] = start_timestamp();
		pthread_mutex_unlock(&box->ptr->death_lock);
		monitoring_states(box, "is eating");
		soft_sleeping(box->ptr->tte);
		monitoring_states(box, "is sleeping");
		pthread_mutex_unlock(&box->ptr->forks[box->l]);
		pthread_mutex_unlock(&box->ptr->forks[box->r]);
		soft_sleeping(box->ptr->tts);
		monitoring_states(box, "is thinking");
		pthread_mutex_lock(&box->ptr->death_lock);
	}
}

void	*thread_preparing(void *arg)
{
	t_data	*box;

	box = (t_data *)arg;
	if (box->ptr->ph_nbr == 1)
	{
		printf("%lld %d has taken a fork\n",
			start_timestamp() - box->ptr->f_time, box->ind);
	}
	else
	{
		philo_loop(box);
		pthread_mutex_unlock(&box->ptr->death_lock);
	}
	return (NULL);
}
