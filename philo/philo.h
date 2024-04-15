/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:43:58 by seohyeki          #+#    #+#             */
/*   Updated: 2024/04/16 01:26:44 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				used;
}				t_fork;

typedef struct s_args
{
	int				philo_num;
	int				alive_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	int				start_flag;
	int				end_flag;
	long			start_time;
	t_fork			*fork;
	pthread_mutex_t	printf;
	pthread_mutex_t	start;
	pthread_mutex_t	end;
}				t_args;

typedef struct s_philo_info
{
	int				id;
	int				left;
	int				right;
	int				eat_count;
	long			last_eat;
	pthread_t		thread;
	t_args			*args;
	pthread_mutex_t	count;
}				t_philo_info;

/*utils*/
int			ft_memcmp(const void *s1, const void *s2, size_t n);
long long	ft_atoi(char *str);
long		get_time(long t);
int			ft_sleep(t_philo_info *info, t_args *args, int act_time);

/*init*/
int			init_args(t_args *args, int argc, char **argv);
int			init_mutex(t_args *args);
int			init_philo_info(t_args *args, t_philo_info **philo);

/*routine*/
void		printing(t_philo_info *info, t_args *args, char *msg);
int			checking(t_philo_info *info, t_args *args);
int			take_fork(t_philo_info *info, t_args *args);
int			eating(t_philo_info *info, t_args *args);
int			sleeping(t_philo_info *info, t_args *args);

#endif