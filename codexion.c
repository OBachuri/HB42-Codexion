/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:32:15 by obachuri          #+#    #+#             */
/*   Updated: 2026/02/25 16:45:16 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int arga, char **args)
{
	if (arga != 9)
	{
		fprintf(stderr, "Error: Wrong papameters! "
			"Run the program with like this: \n");
		fprintf(stderr, "%s  <number_of_coders> "
			"<time_to_burnout time_to_compile> "
			"<time_to_debug> <time_to_refactor> <number_of_compiles_required> "
			"<dongle_cooldown> <scheduler:fifo|edf> \n", args[0]);
		return (1);
	}
	return (0);
}
