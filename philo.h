/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:38:27 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/29 22:56:28 by mel-mouh         ###   ########.fr       */
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
	int	ph_nbr;							//number of philosophers
	pthread_t		philos[MAX_PHILOS];	//arr of thread id
	pthread_mutex_t	*forks;				//pointer to fork arr[ph_nbr]
	size_t			ttd;				//time to die
	size_t			tte;				//time to eat
	size_t			tts;				//time to sleep
	ssize_t			nte;				//nbr of times the philo must eat
	long long	f_time;
}	t_philo;

typedef struct s_data
{
	int				ind;				//position of the philo to keep track of it's poisition
	t_philo			*ptr;				//ptr to t_philo struct
}	t_data;

// MAX_PHILOS * sizeof (int) + sizeof (t_philo *)

void	print_data(t_philo *box);

#endif