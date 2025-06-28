/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:50:26 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/28 21:54:01 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_err(void)
{
	write(2, "number of arguments is less than expected\n", 43);
}

int	start_timestamp(void)
{
	struct timeval pp;
	
	gettimeofday(&pp, NULL);
	return (pp.tv_sec * 1000L + pp.tv_usec / 1000);
}

void	*thread_routine(void *arg)
{
	t_data box;
	
	box = *(t_data *)arg;
	if (box.ind % 2 == 0)
		usleep(200);
	unsigned long int time = box.ptr->f_time;
	while (1)
	{
		if (box.ind < box.ptr->ph_nbr)
			pthread_mutex_lock(&box.ptr->forks[box.ind]);
		else
			pthread_mutex_lock(&box.ptr->forks[0]);
		pthread_mutex_lock(&box.ptr->forks[box.ind - 1]);
		printf("%ld %d is taken the forks\n", start_timestamp() - time, box.ind);
		printf("%ld %d is eating\n", start_timestamp() - time, box.ind);
		usleep(box.ptr->tte);
		pthread_mutex_unlock(&box.ptr->forks[box.ind - 1]);
		if (box.ind < box.ptr->ph_nbr)
			pthread_mutex_unlock(&box.ptr->forks[box.ind]);
		else
			pthread_mutex_unlock(&box.ptr->forks[0]);
		printf("%ld %d is sleeping\n", start_timestamp() - time, box.ind);
		usleep(box.ptr->tts);
		printf("%ld %d is thinking\n", start_timestamp() - time, box.ind);
	}
	return (NULL);
}

bool	analyse_data_nd_store(char **arg, t_philo *box)
{
	int	i;
	memset(box->philos, 0, MAX_PHILOS * sizeof(pthread_t));
	box->ph_nbr = atoi(0[arg]);
	box->ttd = atoi(1[arg]);
	box->tts = atoi(2[arg]);
	box->tte = atoi(3[arg]);
	if (4[arg])
		box->nte = atoi(4[arg]);
	else
		box->nte = -1;
	box->forks = malloc(sizeof(pthread_mutex_t) * box->ph_nbr);
	if (!box->forks)
		return (false);
	i = 0;
	while (i < box->ph_nbr)
	{
		if (pthread_mutex_init(&box->forks[i], NULL))
			return (perror("philo"), false);
		i++;
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_philo	ph_box;
	t_data	data[MAX_PHILOS];
	int		i;

	ph_box.f_time = start_timestamp();
	if (ac < 5)
		return (print_err(), 1);
	analyse_data_nd_store(av + 1, &ph_box);
	print_data(&ph_box);
	i = 1;
	while (i <= ph_box.ph_nbr)
	{
		data[i - 1].ind = i;
		data[i - 1].ptr = &ph_box;
		pthread_create(&ph_box.philos[i - 1], NULL, thread_routine, &data[i - 1]);
		i++;
	}
	while (1);
	return (0);
}