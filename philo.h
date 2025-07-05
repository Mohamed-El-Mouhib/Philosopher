/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:38:27 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/07/05 10:59:44 by mel-mouh         ###   ########.fr       */
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
# define IMX 2147483647

typedef struct s_philo
{
	int				ph_nbr;
	pthread_t		philos[MAX_PHILOS];
	pthread_mutex_t	forks[MAX_PHILOS];
	size_t			ttd;
	size_t			tte;
	size_t			tts;
	ssize_t			nte;
	size_t			f_time;
	pthread_mutex_t	death_lock;
	size_t			last_meal[MAX_PHILOS];
	bool			some_dead;
	ssize_t			eat_n[MAX_PHILOS];
}	t_philo;

typedef struct s_data
{
	int				ind;
	t_philo			*ptr;
}	t_data;

bool		check_args(char **arg);
int			print_err(int errnum);
long long	start_timestamp(void);
void		print_data(t_philo *box);
void		*thread_preparing(void *arg);
void		*monitoring_routing(void *arg);
void		soft_sleeping(long long duration);
void		monitoring_states(t_data *box, char *str);
bool		analyse_data_nd_store(char **arg, t_philo *box);

#endif