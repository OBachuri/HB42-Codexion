/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minpqueue.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:51:02 by obachuri          #+#    #+#             */
/*   Updated: 2026/03/17 20:24:15 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Priority queue - min - (Min Heap with Binary Heap Structure)

#ifndef MINPQUEUE_H
# define MINPQUEUE_H

# include <stdlib.h>

# ifndef PQ_INIT_SIZE
#  define PQ_INIT_SIZE 20024
# endif

// value - sort by that 
typedef struct s_qelement
{
	long			sort;
	unsigned int	id;
	void			*data;
}	t_qelement;

typedef struct s_pqueue
{
	unsigned long	capacity;
	unsigned long	len;
	unsigned long	id;
	t_qelement		*qe;
}	t_pqueue;

t_pqueue	*pq_init(void);
void		pq_clean(t_pqueue **q_);
int			pq_insert(t_pqueue *q, long sort, void *data);

void		*pq_peek(t_pqueue *q);	// return pointer to data
void		*pq_pop(t_pqueue *q);	// return pointer to data

#endif
