/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:32:15 by obachuri          #+#    #+#             */
/*   Updated: 2026/03/19 18:01:55 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"./coders/codexion.h"

int	main(int arga, char **args)
{
	t_param	param;

	if (arga != 9)
		return (
			fprintf(stderr, "Error: Wrong papameters! "
				"Run the program like this: \n"),
			fprintf(stderr, "%s  <number_of_coders> "
				"<time_to_burnout> <time_to_compile> <time_to_debug> "
				"<ti1me_to_refactor> <number_of_compiles_required> "
				"<dongle_cooldown> <scheduler:fifo|edf> \n", args[0]), 1);
	if (param_read_test(&param, args))
		return (1);
	if (init_simulation(&param))
		return (1);
	usleep(6000);
	log_print(&param);
	printf("Coders completed task = %d from %d, result: ",
		param.coders_complete_task, param.number_of_coders);
	if (param.it_is_the_end == 2)
		printf("Task completed.\n");
	else
		printf("Coder burned out.\n");
	cleanup(&param);
	return (0);
}
