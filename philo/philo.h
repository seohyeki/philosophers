/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:43:58 by seohyeki          #+#    #+#             */
/*   Updated: 2024/04/08 20:23:08 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_args
{
	int				philo_num;
	int				alive_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	long			start;
	pthread_mutex_t	*fork;
	pthread_mutex_t	printf;
}				t_args;

typedef struct s_philo_info
{
	int		id;
	int		left;
	int		right;
	int		eat_count;
	long	last_eat;
	t_args	*args;
}				t_philo_info;

/*utils*/
long long	ft_atoi(char *str);
long		get_time(long t);

/*init*/
int			init_args(t_args *args, int argc, char **argv);
int			init_mutex(t_args *args);
int			init_philo_info(t_args *args, t_philo_info **philo);

#endif