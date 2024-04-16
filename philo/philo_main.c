/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:10:17 by seohyeki          #+#    #+#             */
/*   Updated: 2024/04/16 19:05:57 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>

void	act_loop(t_args *args, t_philo_info *info)
{
	while (1)
	{
		pthread_mutex_lock(&args->end);
		if (args->end_flag)
		{
			pthread_mutex_unlock(&args->end);
			return ;
		}
		pthread_mutex_unlock(&args->end);
		if (take_fork(info, args))
		{
			if (eating(info, args))
				break ;
			if (sleeping(info, args))
				break ;
			usleep(args->alive_time * 20);
		}
	}
}

void	*acting(void *arg)
{
	t_philo_info	*info;
	t_args			*args;

	info = (t_philo_info *)arg;
	args = info->args;
	while (1)
	{
		pthread_mutex_lock(&args->start);
		if (args->start_flag)
		{
			info->last_eat = args->start_time;
			pthread_mutex_unlock(&args->start);
			break ;
		}
		pthread_mutex_unlock(&args->start);
	}
	if (info->id % 2 == 0)
		usleep(args->alive_time * 20);
	act_loop(args, info);
	return (0);
}

int	finishing(t_args *args, t_philo_info **info)
{
	int	i;

	i = 0;
	while (i < args->philo_num)
	{
		pthread_join((*info)[i].thread, NULL);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_args			args;
	t_philo_info	*info;
	int				i;

	if ((argc != 5 && argc != 6) || init_args(&args, argc, argv))
		return (1);
	if (init_philo_info(&args, &info))
		return (1);
	i = 0;
	while (i < args.philo_num)
	{
		pthread_create(&info[i].thread, NULL, acting, &info[i]);
		i++;
	}
	args.start_time = get_time(0);
	pthread_mutex_lock(&args.start);
	args.start_flag = 1;
	pthread_mutex_unlock(&args.start);
	if (args.must_eat)
		monitering(&args, info);
	if (finishing(&args, &info))
		return (1);
	return (0);
}
