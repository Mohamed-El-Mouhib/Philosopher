/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:50:26 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/07/03 13:23:43 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// it just print the error in stderr
int	print_err(int errnum)
{
	if (errnum == 1)
		write(2, "philo: number of arguments is not valid\n", 41);
	else if (errnum == 2)
		write(2, "philo: numeric argument required\n", 34);
	else if (errnum == 3)
		write(2, "philo: error occurred while init mutex\n", 40);
	return (1);
}

// this gets the time sence the Epoch in ms
long long	start_timestamp(void)
{
	struct timeval pp;

	gettimeofday(&pp, NULL);
	return ((pp.tv_sec * 1000) + (pp.tv_usec / 1000));
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

// this analyse and parse the arguments passed to philo and store em in t_philo struct
bool	analyse_data_nd_store(char **arg, t_philo *box)
{
	int	i;

	if (!check_args(arg))
		return (print_err(2), false);
	box->ph_nbr = atoi(0[arg]);
	box->ttd = atoi(1[arg]);
	box->tts = atoi(2[arg]);
	box->tte = atoi(3[arg]);
	memset(box->philos, 0, box->ph_nbr * sizeof(pthread_t));
	box->nte = -1;
	if (4[arg])
		box->nte = atoi(4[arg]);
	i = 0;
	while (i < box->ph_nbr)
	{
		box->last_meal[i] = box->f_time;
		if (pthread_mutex_init(&box->forks[i], NULL))
			return (print_err(3), false);
		i++;
	}
	box->some_dead = false;
	if (pthread_mutex_init(&box->death_lock, NULL))
		return(print_err(3), false);
	return (true);
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
	// print_data(&ph_box);
	tmp = pthread_create(&tmp, NULL, monitoring_routing, &ph_box);
	i = 1;
	while (i <= ph_box.ph_nbr)
	{
		data[i - 1].ind = i;
		data[i - 1].ptr = &ph_box;
		pthread_create(&ph_box.philos[i - 1], NULL, thread_routine, &data[i - 1]);
		i++;
	}
	i = 0;
	pthread_join(tmp, NULL);
	while (i < ph_box.ph_nbr)
	{
		pthread_join(ph_box.philos[i], NULL);
		i++;
	}
	return (0);
}
