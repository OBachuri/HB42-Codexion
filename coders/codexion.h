/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:48:51 by obachuri          #+#    #+#             */
/*   Updated: 2026/03/04 13:33:26 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include	<stdio.h>
# include	<unistd.h>
# include	<stdlib.h>
# include	<limits.h>
# include	<string.h>
# include	<pthread.h>
# include	<sys/time.h> 

typedef enum e_scheduler {FIFO, EDF}	t_scheduler;
/* fifo - First In, First Out: the dongle is granted to the coder whose
request arrived first.
edf - means Earliest Deadline First with deadline = last_compile_start +
time_to_burnout.
*/

typedef struct s_coder	t_coder; // forward declaration

typedef struct s_dongle
{
	int				id;
	unsigned long	end_of_last_use;
	pthread_mutex_t	dongle_mutex;
}	t_dongle;

typedef struct s_param
{
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;	
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	t_scheduler		scheduler;
	unsigned long	start_time;
	pthread_mutex_t	print_mutex;
	int				it_is_the_end;
	pthread_mutex_t	it_is_the_end_mutex;
	t_coder			*coders;
	t_dongle		*dongles;
}	t_param;

typedef struct s_coder
{
	int				id;
	int				times_compile;
	long			time_last_compile;
	pthread_mutex_t	*left_dongle;
	pthread_mutex_t	*right_dongle;
	t_param			*param;
	pthread_t		thread_id;

}	t_coder;

int		param_read_test(t_param	*param, char **args);
int		init_simulation(t_param	*param);
void	print_status(t_coder *coder, const char *status, unsigned long time_ms);
void	print_status_curr_time(t_coder *coder, const char *status);
void	cleanup(t_param *param);
void	exit_error(t_param *param, char *error);
int		is_it_the_end(t_param	*param);

void	*coder_routine(void *arg);

long	fm_get_time_ms(void);
size_t	ft_strlcpy(char *dest_, const char *src_, size_t cnt_);
char	*ft_strdup(const char *string);
char	*ft_strchr(const char *str, int c);
char	*fm_str_trim(char *str_, char *c_set_);
char	fm_isspace(const char c_);
ssize_t	fm_atoi_l(const char *str);
char	*ft_itoa(int n);

#endif