/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:50:26 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/07/03 10:36:48 by mel-mouh         ###   ########.fr       */
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
	return ((pp.tv_sec * 1000L) + (pp.tv_usec / 1000));
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
		usleep(100);
	}
}

void *monitoring_routing(void *arg)
{
	int			i;
	t_philo		*box;
	long long	now;

	box = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < box->ph_nbr)
		{
			pthread_mutex_lock(&box->death_lock);
			now = start_timestamp();
			if ((now - box->last_meal[i] >= box->ttd) || (box->nte >= 0 && box->nte == box->eat_n[i]))
			{
				printf("%lld %d is died\n", now - box->f_time, i + 1);
				box->some_dead = true;
				pthread_mutex_unlock(&box->death_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&box->death_lock);
			i++;
		}
		soft_sleeping(1);
	}
	return (NULL);
}

// it print in stdout the timestamps and philo id and str as it's status
void	monitoring_states(t_data *box, char *str)
{
	long long	now;

	now = start_timestamp();
	pthread_mutex_lock(&box->ptr->death_lock);
	if (!box->ptr->some_dead)
		printf("%lld %d %s\n", now - box->ptr->f_time, box->ind, str);
	pthread_mutex_unlock(&box->ptr->death_lock);
}

// it simulate a philosopher (eats, sleep, think, die)
void *thread_routine(void *arg)
{
	t_data	*box; //the struct
	int		left; //left fork
	int		right; //right fork
	bool	rev_oder;

	box = (t_data *)arg;
	right = box->ind - 1;
	rev_oder = false;
	if (box->ind == box->ptr->ph_nbr)
		left = 0;
	else
		left = box->ind;
	if (box->ind % 2 == 0)
	{
		rev_oder = true;
		usleep(500);
	}
	pthread_mutex_lock(&box->ptr->death_lock);
	box->ptr->last_meal[box->ind - 1] = start_timestamp();
	pthread_mutex_unlock(&box->ptr->death_lock);
	while (!box->ptr->some_dead)
	{
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
	}
    return NULL;
}

// this analyse and parse the arguments passed to philo and store em in t_philo struct
bool	analyse_data_nd_store(char **arg, t_philo *box)
{
	int	i;
	box->ph_nbr = atoi(0[arg]);
	box->ttd = atoi(1[arg]);
	box->tts = atoi(2[arg]);
	box->tte = atoi(3[arg]);
	memset(box->philos, 0, box->ph_nbr * sizeof(pthread_t));
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
		box->last_meal[i] = box->f_time;
		if (pthread_mutex_init(&box->forks[i], NULL))
			return (perror("philo"), false);
		i++;
	}
	box->some_dead = false;
	pthread_mutex_init(&box->print_access, NULL);
	memset(box->eat_n, 0, sizeof(int) * MAX_PHILOS);
	return (true);
}

int	main(int ac, char **av)
{
	t_philo		ph_box;
	t_data		data[MAX_PHILOS];
	pthread_t	tmp;
	int			i;

	ph_box.f_time = start_timestamp();
	if (ac < 5)
		return (print_err(), 1);
	analyse_data_nd_store(av + 1, &ph_box);
	print_data(&ph_box);
	pthread_mutex_init(&ph_box.death_lock, NULL);
	tmp = pthread_create(&tmp, NULL, monitoring_routing, &ph_box);
	i = 1;
	while (i <= ph_box.ph_nbr)
	{
		data[i - 1].ind = i;
		data[i - 1].ptr = &ph_box;
		pthread_create(&ph_box.philos[i - 1], NULL, thread_routine, &data[i - 1]);
		i++;
	}
	pthread_join(ph_box.philos[0], NULL);
	return (0);
}
