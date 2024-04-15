/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:50:11 by seohyeki          #+#    #+#             */
/*   Updated: 2024/04/16 00:57:19 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	init_args(t_args *args, int argc, char **argv)
{
	args->philo_num = (int)ft_atoi(argv[1]);
	args->alive_time = (int)ft_atoi(argv[2]);
	args->eat_time = (int)ft_atoi(argv[3]);
	args->sleep_time = (int)ft_atoi(argv[4]);
	if (args->philo_num <= 0 || args->alive_time < 0
		|| args->eat_time < 0 || args->sleep_time < 0)
		return (1);
	if (argc == 6)
	{
		args->must_eat = (int)ft_atoi(argv[5]);
		if (args->must_eat <= 0)
			return (1);
	}
	else
		args->must_eat = 0;
	args->start_flag = 0;
	args->end_flag = 0;
	return (0);
}

int	init_mutex(t_args *args)
{
	int	i;

	pthread_mutex_init(&args->printf, NULL);
	pthread_mutex_init(&args->end, NULL);
	pthread_mutex_init(&args->start, NULL);
	args->fork = (t_fork *)malloc(sizeof(t_fork) * (args->philo_num));
	if (!args->fork)
		return (1);
	i = 0;
	while (i < args->philo_num)
	{
		pthread_mutex_init(&(args->fork[i].mutex), NULL);
		args->fork[i].used = 0;
		i++;
	}
	return (0);
}

int	init_philo_info(t_args *args, t_philo_info **info)
{
	int	i;

	i = 0;
	*info = (t_philo_info *)malloc(sizeof(t_philo_info) * (args->philo_num));
	if (!(*info))
		return (1);
	while (i < args->philo_num)
	{
		(*info)[i].id = i + 1;
		(*info)[i].left = i;
		(*info)[i].right = (i + 1) % args->philo_num;
		(*info)[i].eat_count = 0;
		(*info)[i].args = args;
		pthread_mutex_init(&((*info)[i].count), NULL);
		i++;
	}
	return (0);
}
