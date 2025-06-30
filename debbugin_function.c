/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debbugin_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:27:56 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/30 16:39:01 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

# define RESET       "\033[0m"
# define RED         "\033[0;31m"
# define GREEN       "\033[0;32m"
# define YELLOW      "\033[0;33m"
# define BLUE        "\033[0;34m"
# define MAGENTA     "\033[0;35m"
# define CYAN        "\033[0;36m"
# define WHITE       "\033[0;37m"
# define BOLD        "\033[1m"
# define BOLD_GREEN  "\033[1;32m"
# define BOLD_RED    "\033[1;31m"
# define BG_GREEN    "\033[42m"
# define BG_RED      "\033[41m"
# define BG_YELLOW   "\033[43m"

void	print_data(t_philo *box)
{
	printf("\t┌───────────────────────────────────────┐\n");
	printf("\t│struct  s_philo\t\t\t│\n");
	printf("\t│\t├ph_nbr\t=");
	printf(GREEN"\t%d"RESET, box->ph_nbr);
	printf(";\t\t│\n");
	printf("\t│\t├ttd   \t=");
	printf(GREEN"\t%zu"RESET, box->ttd);
	printf(";\t\t│\n");
	printf("\t│\t├tts   \t=");
	printf(GREEN"\t%zu"RESET, box->tts);
	printf(";\t\t│\n");
	printf("\t│\t├tte   \t=");
	printf(GREEN"\t%zu"RESET, box->tte);
	printf(";\t\t│\n");
	printf("\t│\t└nte   \t=");
	if (box->nte > 0)
		printf(GREEN"\t%zu"RESET, box->nte);
	else
		printf(RED"\t%ld"RESET, box->nte);
	printf(";\t\t│\n");
	printf("\t└───────────────────────────────────────┘\n");
}
