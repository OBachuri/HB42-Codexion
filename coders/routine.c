/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:50:31 by obachuri          #+#    #+#             */
/*   Updated: 2026/03/01 16:11:01 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"codexion.h"

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
		// compiling
		// debugging	
		// refactoring	
		usleep(1000);
	return (NULL);
}
