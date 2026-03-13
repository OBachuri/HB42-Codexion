/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:48:51 by obachuri          #+#    #+#             */
/*   Updated: 2026/03/13 18:01:26 by obachuri         ###   ########.fr       */
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
# include	<time.h>
# include	<errno.h>

typedef enum e_scheduler {FIFO, EDF}	t_scheduler;
/* fifo - First In, First Out: the dongle is granted to the coder whose
request arrived first.
edf - means Earliest Deadline First with deadline = last_compile_start +
time_to_burnout.
*/

typedef struct s_coder	t_coder; // forward declaration

typedef struct s_request
{
	int				coder_id;
	unsigned long	add_time;
	unsigned long	last_compile;
}	t_request;

typedef struct s_queue
{
	t_request	el[2];
	int			size;
}	t_queue;

typedef struct s_dongle
{
	int				id;
	unsigned long	end_of_last_use;
	int				is_used_now;
	int				coder_id_use_now;
	t_queue			queue;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
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
	int				coders_complete_task;
	pthread_mutex_t	coders_complete_task_mutex;
	pthread_t		monitor_thread_id;
}	t_param;

typedef struct s_coder
{
	int				id;
	int				times_compile;
	unsigned long	last_compile;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	pthread_mutex_t	mutex;
	t_param			*param;
	pthread_t		thread_id;

}	t_coder;

int				param_read_test(t_param	*param, char **args);
int				init_simulation(t_param	*param);
void			print_status(t_coder *coder, const char *status,
					unsigned long time_ms);
void			print_status_curr_time(t_coder *coder, const char *status);
void			cleanup(t_param *param);
void			exit_error(t_param *param, char *error);
int				is_it_the_end(t_param	*param);

void			*coder_routine(void *arg);
void			*monitor_of_burn_out(void *arg);

void			take_dongles(t_coder *c_);

void			queue_add(t_dongle *d_, t_coder *c_);
int				queue_pop(t_dongle *d_, t_scheduler scheduler);
int				queue_peek(t_dongle *d_, t_scheduler scheduler);

unsigned long	fm_get_time_ms(void);
void			s_ms_sleep(t_param	*param, unsigned long ms);

size_t			ft_strlcpy(char *dest_, const char *src_, size_t cnt_);
char			*ft_strdup(const char *string);
char			*ft_strchr(const char *str, int c);
char			*fm_str_trim(char *str_, char *c_set_);
char			fm_isspace(const char c_);
ssize_t			fm_atoi_l(const char *str);
char			*ft_itoa(int n);

#endif