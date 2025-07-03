/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:38:27 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/07/03 18:08:24 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

# define MAX_PHILOS 200

typedef struct s_philo
{
	int	ph_nbr;								//number of philosophers
	pthread_t		philos[MAX_PHILOS];		//arr of thread id
	pthread_mutex_t	forks[MAX_PHILOS];		//pointer to fork arr[ph_nbr]
	size_t			ttd;					//time to die
	size_t			tte;					//time to eat
	size_t			tts;					//time to sleep
	ssize_t			nte;					//nbr of times the philo must eat
	size_t			f_time;					//time of the start of program
	pthread_mutex_t	death_lock;				//mutex to protec the shared memory lm[ph_nbr]
	size_t			last_meal[MAX_PHILOS];	//arr of last meal times of each philo
	bool			some_dead;				//boolean to check if some philo is dead
	ssize_t			eat_n[MAX_PHILOS];		//arr of nbr times each philo eaten
}	t_philo;

typedef struct s_data
{
	int				ind;					//position of the philo to keep track of it's poisition
	t_philo			*ptr;					//ptr to t_philo struct
}	t_data;

bool		check_args(char **arg);
int			print_err(int errnum);
long long	start_timestamp(void);
void		print_data(t_philo *box);
void		*thread_routine(void *arg);
void		*monitoring_routing(void *arg);
void		soft_sleeping(long long duration);
void		monitoring_states(t_data *box, char *str);
bool		analyse_data_nd_store(char **arg, t_philo *box);

#endif