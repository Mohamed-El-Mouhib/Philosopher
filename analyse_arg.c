/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:15:30 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/07/09 15:50:37 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_args(char **arg)
{
	int (i), (j), (len), (toggle);
	i = -1;
	while (arg[++i])
	{
		j = -1;
		toggle = 0;
		len = 0;
		if (arg[i][0] == '+')
			j++;
		while (arg[i][++j])
		{
			if (arg[i][j] < '0' || arg[i][j] > '9')
				return (false);
			else if (arg[i][j] == '0' && toggle)
				continue ;
			else if (arg[i][j] >= '0' && arg[i][j] <= '9')
			{
				len++;
				toggle = false;
			}
		}
		if (len >= 20)
			return (false);
	}
	return (true);
}

void	exiter_(t_philo *box, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&box->forks[i]);
		i--;
	}
	pthread_mutex_destroy(&box->death_lock);
	pthread_mutex_destroy(&box->meal_update);
	print_err(3);
}

bool	init_mutex(t_philo *box)
{
	int	i;

	if (pthread_mutex_init(&box->meal_update, NULL))
		return (false);
	if (pthread_mutex_init(&box->death_lock, NULL))
	{
		pthread_mutex_destroy(&box->meal_update);
		return (false);
	}
	i = -1;
	while (++i < box->ph_nbr)
	{
		box->last_meal[i] = box->f_time;
		if (pthread_mutex_init(&box->forks[i], NULL))
			return (exiter_(box, i), false);
	}
	return (true);
}

bool	analyse_data_nd_store(char **arg, t_philo *box)
{
	if (!check_args(arg))
		return (print_err(2), false);
	box->ph_nbr = atoi(arg[0]);
	box->ttd = atoi(arg[1]);
	box->tte = atoi(arg[2]);
	box->tts = atoi(arg[3]);
	if (!box->ph_nbr || box->ph_nbr > 200 || box->tte > IMX || box->tts > IMX)
		return (print_err(2), false);
	box->nte = -1;
	if (arg[4])
		box->nte = atoi(arg[4]);
	memset(box->philos, 0, box->ph_nbr * sizeof(pthread_t));
	memset(box->eat_n, 0, sizeof(int) * MAX_PHILOS);
	if (!init_mutex(box))
		return (false);
	return (true);
}
