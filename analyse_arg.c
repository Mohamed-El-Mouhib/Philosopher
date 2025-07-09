/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:15:30 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/07/09 19:19:09 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	long int	numbers;
	int			sign;

	i = 0;
	numbers = 0;
	sign = 1;
	if (!str)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '+')
			;
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		numbers = numbers * 10 + (str[i] - '0');
		i++;
	}
	return (numbers * sign);
}

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
	box->ph_nbr = ft_atoi(arg[0]);
	box->ttd = ft_atoi(arg[1]);
	box->tte = ft_atoi(arg[2]);
	box->tts = ft_atoi(arg[3]);
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
