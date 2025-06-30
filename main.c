/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:50:26 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/30 16:34:03 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// it just print the error in stderr
void	print_err(void)
{
	write(2, "number of arguments is less than expected\n", 43);
}

// this gets the time sence the Epoch in ms
long long	start_timestamp(void)
{
	struct timeval pp;
	
	gettimeofday(&pp, NULL);
	return (((long long)pp.tv_sec * 1000L) + (pp.tv_usec / 1000));
}

// it takes the duration and iterate till it spend it witouth overusing the cpu
void	soft_sleeping(long long duration)
{
	long	start;
	long	now;

	start = start_timestamp();
	while (1)
	{
		now = start_timestamp();
		if (now - start >= duration)
			break;
		usleep(1000);
	}
}

// it simulate a philosopher (eats, sleep, think, die)
void *thread_routine(void *arg)
{
	t_data	box;
	int		left;
	int		right;

	box = *(t_data *)arg;
	right = box.ind - 1;
	if (box.ind == box.ptr->ph_nbr)
		left = 0;
	else
		left = box.ind;
	if (box.ind % 2 == 0)
		soft_sleeping(100);
	while (1)
	{
		if (box.ind % 2 == 0)
		{
			pthread_mutex_lock(&box.ptr->forks[right]);
			printf("%lld %d is taking fork\n", start_timestamp() - box.ptr->f_time, box.ind);
			pthread_mutex_lock(&box.ptr->forks[left]);
		}
		else
		{
			pthread_mutex_lock(&box.ptr->forks[left]);
			printf("%lld %d is taking fork\n", start_timestamp() - box.ptr->f_time, box.ind);
			pthread_mutex_lock(&box.ptr->forks[right]);
		}
		printf("%lld %d is eating\n", start_timestamp() - box.ptr->f_time, box.ind);
		soft_sleeping(box.ptr->tte);
		printf("%lld %d is sleeping\n", start_timestamp() - box.ptr->f_time, box.ind);
		pthread_mutex_unlock(&box.ptr->forks[left]);
		pthread_mutex_unlock(&box.ptr->forks[right]);
		soft_sleeping(box.ptr->tts);
		printf("%lld %d is thinking\n", start_timestamp() - box.ptr->f_time, box.ind);
	}
    return NULL;
}

// this analyse and parse the arguments passed to philo and store em in t_philo struct
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