/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:28:04 by obachuri          #+#    #+#             */
/*   Updated: 2026/03/01 18:00:09 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"codexion.h"

void	cleanup(t_param *param)
{
	int	i;

	if (!param)
		return ;
	pthread_mutex_destroy(&param->print_mutex);
	pthread_mutex_destroy(&param->it_is_the_end_mutex);
	i = -1;
	while (++i < param->number_of_coders)
	{
		if (param->dongles)
			pthread_mutex_destroy(&param->dongles[i]);
	}
	if (param->dongles)
		free(param->dongles);
}

void	exit_error(t_param *param, char *error)
{
	fprintf(stderr, "%s", error);
	cleanup(param);
}
