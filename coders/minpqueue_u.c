/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minpqueue_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 18:50:52 by obachuri          #+#    #+#             */
/*   Updated: 2026/03/16 19:27:21 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minpqueue.h"

t_pqueue	*pq_init(void)
{
	t_pqueue	*q;

	q = malloc(sizeof(t_pqueue));
	if (!q)
		return (q);
	q->qe = malloc(sizeof(t_qelement) * PQ_INIT_SIZE);
	if (!q->qe)
	{
		free(q);
		return (NULL);
	}
	q->id = 0;
	q->capacity = PQ_INIT_SIZE;
	q->len = 0;
	return (q);
}

void	pq_clean(t_pqueue **q_)
{
	unsigned long	id;
	t_pqueue		*q;

	if (!q_)
		return ;
	q = *q_;
	if (!q)
		return ;
	id = 0;
	while (id < q->len)
	{
		if (q->qe[id].data)
			free(q->qe[id].data);
		id++;
	}
	free(q);
	*q_ = NULL;
	return ;
}
