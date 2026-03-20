/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:24:54 by obachuri          #+#    #+#             */
/*   Updated: 2026/03/19 17:51:12 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"codexion.h"

int	init_dongles_and_mutex(t_param	*param)
{
	int	i;

	param->dongles = malloc(sizeof(t_dongle) * param->number_of_coders);
	if (!param->dongles)
		return (exit_error(param, "Error: Alloc memory for dongles\n"), 1);
	i = -1;
	while (++i < param->number_of_coders)
	{
		param->dongles[i].id = i + 1;
		param->dongles[i].queue.size = 0;
		param->dongles[i].end_of_last_use = 0;
		param->dongles[i].is_used_now = 0;
		if (pthread_mutex_init(&param->dongles[i].mutex, NULL))
			return (exit_error(param, "Error: Init dongles mutex \n"), 1);
		if (pthread_cond_init(&param->dongles[i].cond, NULL))
			return (exit_error(param, "Error: Init dongles cond %d\n"), 1);
	}
	if (pthread_mutex_init(&(param->print_mutex), NULL) != 0)
		return (exit_error(param, "Error: Init print mutex\n"), 1);
	if (pthread_mutex_init(&(param->it_is_the_end_mutex), NULL) != 0)
		return (exit_error(param, "Error: Init end simulation mutex\n"), 1);
	if (pthread_mutex_init(&(param->coders_complete_task_mutex), NULL) != 0)
		return (exit_error(param, "Error: Init complete_task mutex\n"), 1);
	return (0);
}

int	init_coders(t_param	*param)
{
	int	i;

	param->coders = malloc(sizeof(t_coder) * param->number_of_coders);
	if (!param->coders)
		return (exit_error(param, "Error: Alloc memory for coders\n"), 1);
	i = -1;
	while (++i < param->number_of_coders)
	{
		param->coders[i].id = i + 1;
		param->coders[i].param = param;
		param->coders[i].times_compile = 0;
		param->coders[i].left_dongle = &(param->dongles[i]);
		if ((i + 1) == param->number_of_coders)
			param->coders[i].right_dongle = &(param->dongles[0]);
		else
			param->coders[i].right_dongle = &(param->dongles[i + 1]);
		if (pthread_mutex_init(&(param->coders[i].mutex), NULL) != 0)
			return (exit_error(param, "Error: Init coder mutex\n"), 1);
	}
	return (0);
}

int	start_simulation(t_param	*param)
{
	int				i;
	unsigned long	now;

	now = fm_get_time_ms();
	param->start_time = now;
	i = -1;
	while (++i < param->number_of_coders)
	{
		param->coders[i].last_compile = now;
		if ((pthread_create(&(param->coders[i].thread_id), NULL,
					coder_routine, &(param->coders[i]))))
			return (exit_error(param, "Error: Start thread of coder.\n"), 1);
	}
	if (pthread_create(&(param->monitor_thread_id), NULL,
			monitor_of_burn_out, param))
		return (exit_error(param, "Error: Start thread for monitor.\n"), 1);
	return (0);
}

int	init_simulation(t_param	*param)
{
	int			err;
	int			i;

	err = init_dongles_and_mutex(param);
	err = err | init_coders(param);
	param->log = pq_init();
	if ((err) || start_simulation(param) || !(param->log))
		return (printf("An error occurred: %d\n", err), 1);
	i = -1;
	while (++i < param->number_of_coders)
		pthread_join(param->coders[i].thread_id, NULL);
	pthread_join(param->monitor_thread_id, NULL);
	return (0);
}
