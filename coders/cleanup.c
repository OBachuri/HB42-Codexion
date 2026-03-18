/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:28:04 by obachuri          #+#    #+#             */
/*   Updated: 2026/03/17 17:50:43 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"codexion.h"

void	cleanup(t_param *param)
{
	int	i;

	if (!param)
		return ;
	pthread_mutex_destroy(&param->print_mutex);
	pthread_mutex_destroy(&param->it_is_the_end_mutex);
	pthread_mutex_destroy(&param->coders_complete_task_mutex);
	if (param->coders)
	{
		i = -1;
		while (++i < param->number_of_coders)
			pthread_mutex_destroy(&param->coders[i].mutex);
		free(param->coders);
	}
	if (param->dongles)
	{
		i = -1;
		while (++i < param->number_of_coders)
		{
			pthread_cond_destroy(&param->dongles[i].cond);
			pthread_mutex_destroy(&param->dongles[i].mutex);
		}
		free(param->dongles);
	}
	pq_clean(&(param->log));
}

void	exit_error(t_param *param, char *error)
{
	fprintf(stderr, "%s", error);
	cleanup(param);
}
