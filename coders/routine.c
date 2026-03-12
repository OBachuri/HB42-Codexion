/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:50:31 by obachuri          #+#    #+#             */
/*   Updated: 2026/03/11 11:42:40 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"codexion.h"

void	compiling(t_coder *c_)
{
	unsigned long	time_;

	take_dongles(c_);
	time_ = fm_get_time_ms();
	if (is_it_the_end(c_->param))
		return ;
	print_status(c_, "has taken a dongle", time_);
	print_status(c_, "has taken a dongle", time_);
	print_status(c_, "is compiling", time_);
	pthread_mutex_lock(&(c_->mutex));
	c_->last_compile = time_;
	c_->times_compile++;
	pthread_mutex_unlock(&(c_->mutex));
	s_ms_sleep(c_->param->time_to_compile);
	time_ += c_->param->time_to_compile;
	pthread_mutex_lock(&(c_->left_dongle->mutex));
	c_->left_dongle->end_of_last_use = time_;
	c_->left_dongle->coder_id_use_now = 0;
	c_->left_dongle->is_used_now = 0;
	pthread_mutex_unlock(&(c_->left_dongle->mutex));
	pthread_mutex_lock(&(c_->right_dongle->mutex));
	c_->right_dongle->end_of_last_use = time_;
	c_->right_dongle->coder_id_use_now = 0;
	c_->right_dongle->is_used_now = 0;
	pthread_mutex_unlock(&(c_->right_dongle->mutex));
}

void	debugging(t_coder *c_)
{
	if (is_it_the_end(c_->param))
		return ;
	print_status_curr_time(c_, "is debugging");
	s_ms_sleep(c_->param->time_to_debug);
}

void	refactoring(t_coder *c_)
{
	if (is_it_the_end(c_->param))
		return ;
	print_status_curr_time(c_, "is refactoring");
	s_ms_sleep(c_->param->time_to_refactor);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	if (coder->param->number_of_coders == 1)
	{
		print_status_curr_time(coder, "has taken a dongle");
		usleep(coder->param->time_to_burnout * 1000);
		return (NULL);
	}
	usleep((coder->id % 2) * 500);
	while (!(is_it_the_end(coder->param)))
	{
		compiling(coder);
		debugging(coder);
		refactoring(coder);
	}
	return (NULL);
}
