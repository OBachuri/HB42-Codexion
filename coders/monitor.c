/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:36:55 by obachuri          #+#    #+#             */
/*   Updated: 2026/03/13 16:31:00 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"codexion.h"

int	check_task_complete(t_param	*param)
{
	pthread_mutex_lock(&(param->coders_complete_task_mutex));
	if (param->coders_complete_task >= param->number_of_coders)
	{
		pthread_mutex_unlock(&(param->coders_complete_task_mutex));
		pthread_mutex_lock(&param->it_is_the_end_mutex);
		param->it_is_the_end = 1;
		pthread_mutex_unlock(&param->it_is_the_end_mutex);
		return (1);
	}
	pthread_mutex_unlock(&(param->coders_complete_task_mutex));
	return (0);
}

int	check_burn_out(t_param	*param)
{
	int				i;
	unsigned long	now;

	now = fm_get_time_ms();
	i = 0;
	while (i < param->number_of_coders)
	{
		pthread_mutex_lock(&(param->coders[i].mutex));
		if (now - param->coders[i].last_compile
			>= (unsigned long)param->time_to_burnout)
		{
			pthread_mutex_lock(&param->it_is_the_end_mutex);
			param->it_is_the_end = 1;
			pthread_mutex_unlock(&param->it_is_the_end_mutex);
			print_status(&(param->coders[i]), "burned out", now);
			pthread_mutex_unlock(&(param->coders[i].mutex));
			return (1);
		}
		pthread_mutex_unlock(&(param->coders[i].mutex));
		i++;
	}
	return (check_task_complete(param));
}

void	*monitor_of_burn_out(void *arg)
{
	t_param	*param;

	param = (t_param *)arg;
	while (!check_burn_out(param))
		usleep(100);
	return (NULL);
}
