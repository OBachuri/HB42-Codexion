/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 18:43:35 by obachuri          #+#    #+#             */
/*   Updated: 2026/02/26 21:03:36 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"codexion.h"

int	fm_max_len_int(void)
{
	char	*s_;
	int		l_;

	l_ = 0;
	s_ = ft_itoa(INT_MAX);
	if (s_)
	{
		l_ = (int)strlen(s_) + 1;
		free (s_);
	}
	return (l_);
}

int	fm_check_is_only_numder(const char *str)
{
	int	i_;
	int	j_;

	i_ = 0;
	j_ = 0;
	while (fm_isspace(str[i_]))
		i_++;
	if ((str[i_] == '-') || (str[i_] == '+'))
		i_++;
	while ((str[i_] >= '0') && (str[i_] <= '9'))
		j_ = ++i_;
	if (!j_)
		return (0);
	str += i_;
	while (*str)
	{
		if (!fm_isspace(*str) && (*str != '-') && (*str != '+') && \
			!((*str >= '0') && (*str <= '9')))
			return (0);
		str++;
	}
	return (i_);
}

ssize_t	fm_atoi_l(const char *str)
{
	ssize_t	i;
	ssize_t	n;

	i = -1;
	n = 0;
	while (fm_isspace(*str))
		str++;
	if (*str == '-')
		i = 1;
	if ((*str == '-') || (*str == '+'))
		str++;
	while ((*str >= '0') && (*str <= '9'))
	{				
		n = n * 10 - (*str - '0');
		str++;
	}
	return (n * i);
}

int	fm_validate_int_param(char **args)
{
	int		i_;
	ssize_t	l_;
	int		max_int_leng;
	char	*str_;

	max_int_leng = fm_max_len_int();
	i_ = 1;
	while (i_ < 8)
	{
		str_ = fm_str_trim(args[i_], " \n\t\v\f");
		l_ = (ssize_t)strlen(str_);
		if ((l_ < 1) || (l_ > max_int_leng))
			return (fprintf(stderr,
					"Error: parameter %d  must be integer >= 0 ! \n", i_), 1);
		l_ = (ssize_t)fm_check_is_only_numder(str_);
		if ((l_ < 1) || (l_ > max_int_leng))
			return (fprintf(stderr,
					"Error: parameter %d  must be integer >= 0 ! \n", i_), 1);
		l_ = fm_atoi_l(str_);
		if ((l_ < 0) || (l_ > INT_MAX))
			return (fprintf(stderr,
					"Error: parameter %d  must be integer >= 0 ! \n", i_), 1);
		i_++;
	}
	return (0);
}

int	param_read_test(t_param	*param, char **args)
{
	char	*str_;

	param->number_of_coders = atoi(args[1]);
	if (fm_validate_int_param(args))
		return (1);
	if (param->number_of_coders < 1)
		return (fprintf(stderr, "Error: number_of_coders must be >0 ! \n"), 1);
	str_ = fm_str_trim(args[8], " \n\t\v\f");
	if (!(strcmp(str_, "fifo")))
		param->scheduler = FIFO;
	else if (!(strcmp(str_, "edf")))
		param->scheduler = EDF;
	else
		return (fprintf(stderr,
				"Error: scheduler must 'fifo' or 'edf' ! \n"), 1);
	param->time_to_burnout = atoi(args[2]);
	param->time_to_compile = atoi(args[3]);
	param->time_to_debug = atoi(args[4]);
	param->time_to_refactor = atoi(args[5]);
	param->number_of_compiles_required = atoi(args[6]);
	param->dongle_cooldown = atoi(args[7]);
	return (0);
}
