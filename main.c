/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:50:26 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/07/04 23:46:44 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_err(int errnum)
{
	if (errnum == 1)
		write(2, "philo: number of arguments is not valid\n", 41);
	else if (errnum == 2)
		write(2, "philo: You need a valid argument\n", 34);
	else if (errnum == 3)
		write(2, "philo: error occurred while init mutex\n", 40);
	else if (errnum == 4)
		write(2, "philo: invalid number of philosophers\n", 39);
	return (1);
}

long long	start_timestamp(void)
{
	struct timeval	pp;

	gettimeofday(&pp, NULL);
	return ((pp.tv_sec * 1000) + (pp.tv_usec / 1000));
}

void	wait_philos(t_philo *box, pthread_t monitor)
{
	int	i;

	i = -1;
	pthread_join(monitor, NULL);
	while (++i < box->ph_nbr)
	{
		pthread_join(box->philos[i], NULL);
		pthread_mutex_destroy(&box->forks[i]);
	}
	pthread_mutex_destroy(&box->death_lock);
}

int	main(int ac, char **av)
{
	t_philo		ph_box;
	t_data		data[MAX_PHILOS];
	pthread_t	tmp;
	int			i;

	if (ac < 5 || ac > 6)
		return (print_err(1));
	ph_box.f_time = start_timestamp();
	if (!analyse_data_nd_store(av + 1, &ph_box))
		return (1);
	ph_box.some_dead = false;
	i = 1;
	while (i <= ph_box.ph_nbr)
	{
		data[i - 1].ind = i;
		data[i - 1].ptr = &ph_box;
		pthread_create(&ph_box.philos[i - 1],
			NULL, thread_preparing, &data[i - 1]);
		i++;
	}
	pthread_create(&tmp, NULL, monitoring_routing, &ph_box);
	wait_philos(&ph_box, tmp);
}
