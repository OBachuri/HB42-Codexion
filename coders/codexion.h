/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:48:51 by obachuri          #+#    #+#             */
/*   Updated: 2026/02/26 20:58:08 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include	<stdio.h>
# include	<unistd.h>
# include	<stdlib.h>
# include	<limits.h>
# include	<string.h>

typedef enum e_scheduler {FIFO, EDF}	t_scheduler;
/* fifo - First In, First Out: the dongle is granted to the coder whose
request arrived first.
edf - means Earliest Deadline First with deadline = last_compile_start +
time_to_burnout.
*/

typedef struct s_param
{
	int			number_of_coders;
	int			time_to_burnout;
	int			time_to_compile;	
	int			time_to_debug;
	int			time_to_refactor;
	int			number_of_compiles_required;
	int			dongle_cooldown;
	t_scheduler	scheduler;

}	t_param;

int		param_read_test(t_param	*param, char **args);

size_t	ft_strlcpy(char *dest_, const char *src_, size_t cnt_);
char	*ft_strdup(const char *string);
char	*ft_strchr(const char *str, int c);
char	*fm_str_trim(char *str_, char *c_set_);
char	fm_isspace(const char c_);
ssize_t	fm_atoi_l(const char *str);
char	*ft_itoa(int n);

#endif