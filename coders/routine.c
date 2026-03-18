/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:50:31 by obachuri          #+#    #+#             */
/*   Updated: 2026/03/17 20:06:35 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"codexion.h"

void	check_if_number_of_compiles_is_required(t_coder *c_)
{
	c_->times_compile++;
	if (c_->times_compile == c_->param->number_of_compiles_required)
	{
		pthread_mutex_lock(&(c_->param->coders_complete_task_mutex));
		c_->param->coders_complete_task++;
		pthread_mutex_unlock(&(c_->param->coders_complete_task_mutex));
	}	
}

void	compiling(t_coder *c_)
{
	unsigned long	time_;

	take_dongles(c_);
	time_ = fm_get_time_ms();
	if (is_it_the_end(c_->param))
		return ;
	pthread_mutex_lock(&(c_->mutex));
	c_->last_compile = time_;
	pthread_mutex_unlock(&(c_->mutex));
	log_add(c_, C_TAKE_DONGLE, time_);
	log_add(c_, C_TAKE_DONGLE, time_);
	log_add(c_, C_COMPILE, time_);
	s_ms_sleep(c_->param, (unsigned long)c_->param->time_to_compile);
	pthread_mutex_lock(&(c_->mutex));
	check_if_number_of_compiles_is_required(c_);
	pthread_mutex_unlock(&(c_->mutex));
	time_ += c_->param->time_to_compile;
	return_dongle_after_compile(c_->left_dongle, time_);
	return_dongle_after_compile(c_->right_dongle, time_);
}

void	debugging(t_coder *c_)
{
	if (is_it_the_end(c_->param))
		return ;
	log_add_curr_time(c_, C_DEBUG);
	s_ms_sleep(c_->param, (unsigned long)c_->param->time_to_debug);
}

void	refactoring(t_coder *c_)
{
	if (is_it_the_end(c_->param))
		return ;
	log_add_curr_time(c_, C_REFACTOR);
	s_ms_sleep(c_->param, (unsigned long)c_->param->time_to_refactor);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	if (coder->param->number_of_coders == 1)
	{
		log_add_curr_time(coder, C_TAKE_DONGLE);
		usleep(coder->param->time_to_burnout * 1000 + 1000);
		return (NULL);
	}
	usleep(((coder->id - 1) % 2) * 500);
	while (!(is_it_the_end(coder->param)))
	{
		compiling(coder);
		debugging(coder);
		refactoring(coder);
	}
	return (NULL);
}
