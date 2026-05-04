/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 11:41:37 by obachuri          #+#    #+#             */
/*   Updated: 2026/05/04 17:50:50 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"codexion.h"

void	return_dongle_after_compile(t_dongle *d_, unsigned long time_)
{
	pthread_mutex_lock(&(d_->mutex));
	d_->end_of_last_use = time_;
	d_->coder_id_use_now = 0;
	d_->is_used_now = 0;
	pthread_mutex_unlock(&(d_->mutex));
}

int	check_dongle_cooldown(t_dongle *d_, t_param	*param)
// return True if dongle is "cooldown" and couldn`t be used now
{
	return ((fm_get_time_ms() - d_->end_of_last_use)
		< (unsigned long)param->dongle_cooldown);
}

// --- for debug put the code in start of return_dongle()
// printf("-- return - coder %d, q_size %d, d_id = %d \n",
// 	c_->id, d_->queue.size, d_->id);
// printf("q[0]: coder %d, last_time %ld \n",
// 	d_->queue.el[0].coder_id, d_->queue.el[0].last_compile);
// if (d_->queue.size > 1)
// 	printf("q[1]: coder %d, last_time %ld \n",
// 		d_->queue.el[1].coder_id, d_->queue.el[1].last_compile);

int	return_dongle(t_dongle *d_, t_coder *c_)
{
	if (c_->id == queue_peek(d_, c_->param->scheduler))
	{
		d_->coder_id_use_now = queue_pop(d_, c_->param->scheduler);
		d_->is_used_now = 1;
		pthread_mutex_unlock(&(d_->mutex));
		return (c_->id);
	}
	pthread_cond_broadcast(&(d_->cond));
	pthread_mutex_unlock(&(d_->mutex));
	return (0);
}

int	take_dongle(t_dongle *d_, t_coder *c_)
{
	struct timespec	ts;
	unsigned long	last_compile;

	pthread_mutex_lock(&(c_->mutex));
	last_compile = c_->last_compile;
	pthread_mutex_unlock(&(c_->mutex));
	pthread_mutex_lock(&(d_->mutex));
	queue_add(d_, c_, last_compile);
	if ((d_->is_used_now) || (check_dongle_cooldown(d_, c_->param)))
		return (pthread_mutex_unlock(&(d_->mutex)),
			usleep(100), 0);
	if (d_->queue.size > 1)
		return (return_dongle(d_, c_));
	delay_ns_in_ts(&ts, 900000);
	pthread_cond_timedwait(&(d_->cond), &(d_->mutex), &ts);
	return (return_dongle(d_, c_));
}

void	take_dongles(t_coder *c_)
{
	while (!(is_it_the_end(c_->param)))
	{
		while (!(take_dongle(c_->left_dongle, c_)))
			if (is_it_the_end(c_->param))
				return ;
		else
			usleep(200);
		if (take_dongle(c_->right_dongle, c_))
			return ;
		pthread_mutex_lock(&(c_->left_dongle->mutex));
		c_->left_dongle->coder_id_use_now = 0;
		c_->left_dongle->is_used_now = 0;
		pthread_mutex_unlock(&(c_->left_dongle->mutex));
		while (!(take_dongle(c_->right_dongle, c_)))
			if (is_it_the_end(c_->param))
				return ;
		else
			usleep(200);
		if (take_dongle(c_->left_dongle, c_))
			return ;
		pthread_mutex_lock(&(c_->right_dongle->mutex));
		c_->right_dongle->coder_id_use_now = 0;
		c_->right_dongle->is_used_now = 0;
		pthread_mutex_unlock(&(c_->right_dongle->mutex));
	}
}
