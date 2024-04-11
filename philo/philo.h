/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:43:58 by seohyeki          #+#    #+#             */
/*   Updated: 2024/04/11 22:22:17 by seohyeki         ###   ########.fr       */
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
	long			start;
	t_fork			*fork;
	pthread_mutex_t	printf;
}				t_args;

typedef struct s_philo_info
{
	int		id;
	int		left;
	int		right;
	int		eat_count;
	long	last_eat;
	int		end_flag;
	t_args	*args;
}				t_philo_info;

/*utils*/
int			ft_memcmp(const void *s1, const void *s2, size_t n);
long long	ft_atoi(char *str);
long		get_time(long t);
int			ft_sleep(t_philo_info *info, long cur_time, int act_time);

/*init*/
int			init_args(t_args *args, int argc, char **argv);
int			init_mutex(t_args *args);
int			init_philo_info(t_args *args, t_philo_info **philo);
int			init_thread(pthread_t **philo, t_args *args, t_philo_info **info, void *acting);

/*routine*/
void	printing(t_philo_info *info, t_args *args, char *msg);
int		eating(t_philo_info *info, t_args *args);
int		sleeping(t_philo_info *info, t_args *args);

#endif