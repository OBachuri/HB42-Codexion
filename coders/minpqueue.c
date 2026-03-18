/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minpqueue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:50:05 by obachuri          #+#    #+#             */
/*   Updated: 2026/03/16 19:28:18 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Priority queue - min - (Min Heap with Binary Heap Structure)

#include	"minpqueue.h"

void	pq_element_swap(t_pqueue *q, unsigned long a_, unsigned long b_)
{
	t_qelement		qe;

	if ((q->len <= a_) || (q->len <= b_))
		return ;
	qe.data = q->qe[a_].data;
	qe.id = q->qe[a_].id;
	qe.sort = q->qe[a_].sort;
	q->qe[a_].data = q->qe[b_].data;
	q->qe[a_].id = q->qe[b_].id;
	q->qe[a_].sort = q->qe[b_].sort;
	q->qe[b_].data = qe.data;
	q->qe[b_].id = qe.id;
	q->qe[b_].sort = qe.sort;
}

int	pq_insert(t_pqueue *q, long sort, void *data)
{
	unsigned long	parent;
	unsigned long	index;

	if (q->len >= q->capacity)
		return (-1);
	q->qe[q->len].data = data;
	q->qe[q->len].sort = sort;
	q->qe[q->len].id = q->id++;
	index = q->len;
	q->len++;
	parent = (index - 1) / 2;
	while ((index > 0) && ((q->qe[parent].sort > q->qe[index].sort)
			|| ((q->qe[parent].sort == q->qe[index].sort)
				&& (q->qe[parent].id > q->qe[index].id))))
	{
		pq_element_swap(q, parent, index);
		index = parent;
		parent = (index - 1) / 2;
	}
	return (q->len);
}

void	*pq_peek(t_pqueue *q)
{
	if (q->len < 1)
		return (NULL);
	return (q->qe->data);
}

// Heapify Down (for Extract)
// When removing the root we:
// Replace root with last element
// Restore heap property

void	pq_heapify_down(t_pqueue *q, unsigned long index)
{
	unsigned long	smallest;
	unsigned long	left;
	unsigned long	right;

	smallest = index;
	left = 2 * index + 1;
	right = 2 * index + 2;
	if ((left < q->len) && (q->qe[left].sort < q->qe[smallest].sort
			|| (q->qe[left].sort == q->qe[smallest].sort
				&& q->qe[left].id < q->qe[smallest].id)))
		smallest = left;
	if ((right < q->len) && (q->qe[right].sort < q->qe[smallest].sort
			|| (q->qe[right].sort == q->qe[smallest].sort
				&& q->qe[right].id < q->qe[smallest].id)))
		smallest = right;
	if (smallest != index)
	{
		pq_element_swap(q, index, smallest);
		pq_heapify_down(q, smallest);
	}
}

void	*pq_pop(t_pqueue *q)
{
	void	*data;

	if (q->len < 1)
		return (NULL);
	data = q->qe->data;
	q->len--;
	if (q->len < 1)
		return (data);
	q->qe[0].data = q->qe[q->len].data;
	q->qe[0].sort = q->qe[q->len].sort;
	q->qe[0].id = q->qe[q->len].id;
	pq_heapify_down(q, 0);
	return (data);
}
