/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:24:54 by obachuri          #+#    #+#             */
/*   Updated: 2026/03/01 18:09:48 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"codexion.h"

int	initialize_mutexes(t_param	*param)
{
	int	i;

	param->dongles = malloc(sizeof(pthread_mutex_t) * param->number_of_coders);
	if (!param->dongles)
		return (exit_error(param, "Error: Alloc memory for dongles\n"), 1);
	i = -1;
	while (++i < param->number_of_coders)
		if (pthread_mutex_init(&param->dongles[i], NULL) != 0)
			return (exit_error(param, "Error: Init fork mutex %d\n"), 1);
	if (pthread_mutex_init(&(param->print_mutex), NULL) != 0)
		return (exit_error(param, "Error: Init print mutex\n"), 1);
	if (pthread_mutex_init(&(param->it_is_the_end_mutex), NULL) != 0)
		return (exit_error(param, "Error: Init end simulation mutex\n"), 1);
	return (0);
}

/*
int pthread_create(
  pthread_t *thread,
  const pthread_attr_t *attr,
  void *(*routine) (void *),
  void *arg);
*/

int	init_simulation(t_param	*param)
{
	pthread_t	thread;
	int			err;

	err = initialize_mutexes(param);
	err = err | pthread_create(&thread, NULL, coder_routine, NULL);
	if (err != 0)
	{
		printf("An error occurred: %d\n", err);
		return (1);
	}
	return (0);
}
