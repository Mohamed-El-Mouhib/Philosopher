/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:15:30 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/07/03 18:28:57 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_args(char **arg)
{
	int	i;
	int	j;

	i = 0;
	while (arg[i])
	{
		j = 0;
		while (arg[i][j])
		{
			if (arg[i][j] < '0' || arg[i][j] > '9')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	analyse_data_nd_store(char **arg, t_philo *box)
{
	int	i;

	if (!check_args(arg))
		return (print_err(2), false);
	box->ph_nbr = atoi(arg[0]);
	box->ttd = atoi(arg[1]);
	box->tts = atoi(arg[2]);
	box->tte = atoi(arg[3]);
	box->nte = -1;
	if (arg[4])
		box->nte = atoi(arg[4]);
	i = -1;
	while (++i < box->ph_nbr)
	{
		box->last_meal[i] = box->f_time;
		if (pthread_mutex_init(&box->forks[i], NULL))
			return (print_err(3), false);
	}
	memset(box->philos, 0, box->ph_nbr * sizeof(pthread_t));
	memset(box->eat_n, 0, sizeof(int) * MAX_PHILOS);
	box->some_dead = false;
	if (pthread_mutex_init(&box->death_lock, NULL))
		return (print_err(3), false);
	return (true);
}
