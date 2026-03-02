/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 13:35:48 by obachuri          #+#    #+#             */
/*   Updated: 2026/03/01 18:11:34 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"codexion.h"

// return current time in miliseconds
long	fm_get_time_ms(void)
{
	struct timeval	tv;
	long			miliseconds;

	gettimeofday(&tv, NULL);
	miliseconds = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (miliseconds);
}

void	print_status(t_coder *coder, const char *status, unsigned long time_ms)
{
	time_ms = time_ms - coder->param->start_time;
	pthread_mutex_lock(&(coder->param->print_mutex));
	printf("%ld %d %s\n", time_ms, coder->id, status);
	pthread_mutex_unlock(&(coder->param->print_mutex));
}

void	print_status_curr_time(t_coder *coder, const char *status)
{
	print_status(coder, status, fm_get_time_ms());
}

int	is_it_the_end(t_param	*param)
{
	int	the_end;

	pthread_mutex_lock(&param->it_is_the_end_mutex);
	the_end = param->it_is_the_end;
	pthread_mutex_unlock(&param->it_is_the_end_mutex);
	return (the_end);
}
