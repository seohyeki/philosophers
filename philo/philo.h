/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:43:58 by seohyeki          #+#    #+#             */
/*   Updated: 2024/04/19 16:29:44 by seohyeki         ###   ########.fr       */
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
	long			philo_num;
	long			alive_time;
	long			eat_time;
	long			sleep_time;
	long			must_eat;
	long			start_time;
	unsigned int	usleep_time;
	int				start_flag;
	int				end_flag;
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
long long	ft_atoi(char *str);
long		get_time(long t);
int			ft_usleep(t_philo_info *info, t_args *args, long cur, long act);
void		ft_printf(t_philo_info *info, t_args *args, char *msg);

/*init*/
int			init_args(t_args *args, int argc, char **argv);
int			init_philo_info(t_args *args, t_philo_info **philo);

/*routine*/
void		routine(t_philo_info *info, t_args *args);
int			monitering(t_args *args, t_philo_info *info);
int			check_end(t_philo_info *info, t_args *args);

#endif