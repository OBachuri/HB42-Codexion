/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:32:15 by obachuri          #+#    #+#             */
/*   Updated: 2026/03/17 21:07:52 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"./coders/codexion.h"

int	main(int arga, char **args)
{
	t_param	param;

	if (arga != 9)
	{
		fprintf(stderr, "Error: Wrong papameters! "
			"Run the program like this: \n");
		fprintf(stderr, "%s  <number_of_coders> "
			"<time_to_burnout> <time_to_compile> "
			"<time_to_debug> <ti1me_to_refactor> <number_of_compiles_required> "
			"<dongle_cooldown> <scheduler:fifo|edf> \n", args[0]);
		return (1);
	}
	if (param_read_test(&param, args))
		return (1);
	if (init_simulation(&param))
		return (1);
	usleep(6000);
	log_print(&param);
	printf("Coders completed task = %d from %d, stop type=%d \n",
		param.coders_complete_task,
		param.number_of_coders, param.it_is_the_end);
	cleanup(&param);
	return (0);
}
