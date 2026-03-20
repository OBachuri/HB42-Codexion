/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 17:15:33 by obachuri          #+#    #+#             */
/*   Updated: 2026/03/19 17:33:04 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"codexion.h"

void	queue_add(t_dongle *d_, t_coder *c_, unsigned long last_compile)
{
	if ((d_->queue.size > 0) && (d_->queue.el[0].coder_id == c_->id))
	{
		if (d_->queue.el[0].last_compile != last_compile)
			d_->queue.el[0].last_compile = last_compile;
		return ;
	}
	if ((d_->queue.size > 1) && (d_->queue.el[1].coder_id == c_->id))
	{
		if (d_->queue.el[1].last_compile != last_compile)
			d_->queue.el[1].last_compile = last_compile;
		return ;
	}
	if (d_->queue.size >= 2)
	{
		fprintf(stderr,
			"ERROR: Can`t add coder %d in queue of dongle %d (c=[%d,%d] )! \n",
			c_->id, d_->id, d_->queue.el[0].coder_id, d_->queue.el[1].coder_id);
		return ;
	}
	d_->queue.el[d_->queue.size].coder_id = c_->id;
	d_->queue.el[d_->queue.size].last_compile = last_compile;
	d_->queue.el[d_->queue.size].add_time = fm_get_time_ms();
	d_->queue.size++;
}

int	queue_pop(t_dongle *d_, t_scheduler scheduler)
{
	int	coder_id;

	if (d_->queue.size < 1)
		return (0);
	if (d_->queue.size < 2)
		return (d_->queue.size--, d_->queue.el[0].coder_id);
	coder_id = d_->queue.el[1].coder_id;
	if (((scheduler == EDF) \
		&& (d_->queue.el[0].last_compile <= d_->queue.el[1].last_compile)) \
		|| ((scheduler == FIFO) \
		&& (d_->queue.el[0].add_time <= d_->queue.el[1].add_time)))
	{
		coder_id = d_->queue.el[0].coder_id;
		d_->queue.el[0].coder_id = d_->queue.el[1].coder_id;
		d_->queue.el[0].last_compile = d_->queue.el[1].last_compile;
		d_->queue.el[0].add_time = d_->queue.el[1].add_time;
	}
	d_->queue.size--;
	return (coder_id);
}

// return element
int	queue_peek(t_dongle *d_, t_scheduler scheduler)
{
	int	coder_id;

	if (d_->queue.size < 1)
		return (0);
	if (d_->queue.size < 2)
		return (d_->queue.el[0].coder_id);
	coder_id = d_->queue.el[1].coder_id;
	if (((scheduler == EDF) \
		&& (d_->queue.el[0].last_compile <= d_->queue.el[1].last_compile)) \
		|| ((scheduler == FIFO) \
		&& (d_->queue.el[0].add_time <= d_->queue.el[1].add_time)))
	{
		coder_id = d_->queue.el[0].coder_id;
	}
	return (coder_id);
}
