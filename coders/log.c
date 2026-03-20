/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:37:26 by obachuri          #+#    #+#             */
/*   Updated: 2026/03/19 17:51:00 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"codexion.h"

void	log_add(t_coder *coder, t_event_type etype, unsigned long time_ms)
{
	t_event	*event;

	if (!(coder->param->log))
		return ;
	time_ms = time_ms - coder->param->start_time;
	event = malloc(sizeof(t_event));
	if (!event)
		fprintf(stderr, "Error: Can`t create event for log (time=%ld) ! \n",
			time_ms);
	event->coder_id = coder->id;
	event->e_type = etype;
	event->time = time_ms;
	pthread_mutex_lock(&(coder->param->print_mutex));
	if (pq_insert(coder->param->log, time_ms, event) < 0)
		fprintf(stderr,
			"Error: Can`t add event to log (time=%ld, log_size=%ld) ! \n",
			time_ms, coder->param->log->len);
	pthread_mutex_unlock(&(coder->param->print_mutex));
}

void	log_add_curr_time(t_coder *coder, t_event_type etype)
{
	log_add(coder, etype, fm_get_time_ms());
}

void	log_print_event(t_event *event)
{
	if (event->e_type == C_TAKE_DONGLE)
		printf("%ld %d has taken a dongle\n", event->time, event->coder_id);
	else if (event->e_type == C_COMPILE)
		printf("%ld %d is compiling\n", event->time, event->coder_id);
	else if (event->e_type == C_DEBUG)
		printf("%ld %d is debugging\n", event->time, event->coder_id);
	else if (event->e_type == C_REFACTOR)
		printf("%ld %d is refactoring\n", event->time, event->coder_id);
	else if (event->e_type == C_BURNOUT)
		printf("%ld %d burned out\n", event->time, event->coder_id);
}

void	log_print(t_param *param)
{
	unsigned long	time_ms;
	t_event			*event;

	time_ms = fm_get_time_ms() - param->start_time;
	pthread_mutex_lock(&(param->print_mutex));
	while ((param->log->len > 0)
		&& (((t_event*)pq_peek(param->log))->time < time_ms - 5))
	{
		event = pq_pop(param->log);
		if (!event)
			continue ;
		log_print_event(event);
		if (((event->e_type == C_BURNOUT) || (event->e_type == C_FINISH))
			&& is_it_the_end(param))
		{
			free(event);
			pq_clean(&(param->log));
			printf("--the end--\n");
			break ;
		}
		free(event);
	}
	pthread_mutex_unlock(&(param->print_mutex));
	return ;
}
