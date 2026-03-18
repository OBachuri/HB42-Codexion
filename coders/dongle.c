/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 11:41:37 by obachuri          #+#    #+#             */
/*   Updated: 2026/03/17 20:45:47 by obachuri         ###   ########.fr       */
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

int	return_dongle(t_dongle *d_, t_coder *c_)
{
	if (c_->id == queue_peek(d_, c_->param->scheduler))
	{
		d_->coder_id_use_now = queue_pop(d_, c_->param->scheduler);
		d_->is_used_now = 1;
		pthread_mutex_unlock(&(d_->mutex));
		return (c_->id);
	}
	pthread_mutex_unlock(&(d_->mutex));
	pthread_cond_broadcast(&(d_->cond));
	return (0);
}

int	take_dongle(t_dongle *d_, t_coder *c_)
{
	struct timespec	ts;

	pthread_mutex_lock(&(d_->mutex));
	pthread_mutex_lock(&(c_->mutex));
	queue_add(d_, c_);
	pthread_mutex_unlock(&(c_->mutex));
	if ((d_->is_used_now) || (check_dongle_cooldown(d_, c_->param)))
		return (pthread_mutex_unlock(&(d_->mutex)),
			usleep(100), 0);
	if (d_->queue.size > 1)
		return (return_dongle(d_, c_));
	delay_ns_in_ts(&ts, 1000);
	pthread_cond_timedwait(&(d_->cond), &(d_->mutex), &ts);
	if (c_->id == queue_peek(d_, c_->param->scheduler))
		return (
			d_->coder_id_use_now = queue_pop(d_, c_->param->scheduler),
			d_->is_used_now = 1,
			pthread_mutex_unlock(&(d_->mutex)),
			c_->id
		);
	else
		return (pthread_mutex_unlock(&(d_->mutex)), 0);
}

void	take_dongles(t_coder *c_)
{
	while (!(is_it_the_end(c_->param)))
	{
		while (!(take_dongle(c_->left_dongle, c_)))
			usleep(200);
		if (take_dongle(c_->right_dongle, c_))
			return ;
		pthread_mutex_lock(&(c_->left_dongle->mutex));
		c_->left_dongle->coder_id_use_now = 0;
		c_->left_dongle->is_used_now = 0;
		pthread_mutex_unlock(&(c_->left_dongle->mutex));
		while (!(take_dongle(c_->right_dongle, c_)))
			usleep(200);
		if (take_dongle(c_->left_dongle, c_))
			return ;
		pthread_mutex_lock(&(c_->right_dongle->mutex));
		c_->right_dongle->coder_id_use_now = 0;
		c_->right_dongle->is_used_now = 0;
		pthread_mutex_unlock(&(c_->right_dongle->mutex));
	}
}
