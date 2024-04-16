/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:39:29 by seohyeki          #+#    #+#             */
/*   Updated: 2024/04/16 17:43:35 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

void	printing(t_philo_info *info, t_args *args, char *msg)
{
	pthread_mutex_lock(&args->printf);
	pthread_mutex_lock(&args->end);
	if (args->end_flag == 0)
		printf("%ld %d %s\n", get_time(args->start_time), info->id, msg);
	pthread_mutex_unlock(&args->end);
	pthread_mutex_unlock(&args->printf);
}

int	checking(t_philo_info *info, t_args *args)
{
	long	live;

	live = get_time(0) - info->last_eat;
	if (args->alive_time - live <= 0)
	{
		pthread_mutex_lock(&args->end);
		if (args->end_flag)
		{
			pthread_mutex_unlock(&args->end);
			return (1);
		}
		pthread_mutex_unlock(&args->end);
		printing(info, args, "died");
		pthread_mutex_lock(&args->end);
		args->end_flag = 1;
		pthread_mutex_unlock(&args->end);
		return (1);
	}
	return (0);
}

int	take_fork(t_philo_info *info, t_args *args)
{
	pthread_mutex_lock(&args->fork[info->left].mutex);
	if (args->fork[info->left].used == 0)
	{
		args->fork[info->left].used = 1;
		pthread_mutex_unlock(&args->fork[info->left].mutex);
		pthread_mutex_lock(&args->fork[info->right].mutex);
		if (args->fork[info->right].used == 0)
		{
			printing(info, args, "has taken a fork");
			args->fork[info->right].used = 1;
			pthread_mutex_unlock(&args->fork[info->right].mutex);
			printing(info, args, "has taken a fork");
			return (1);
		}
		else
		{
			pthread_mutex_unlock(&args->fork[info->right].mutex);
			pthread_mutex_lock(&args->fork[info->left].mutex);
			args->fork[info->left].used = 0;
			pthread_mutex_unlock(&args->fork[info->left].mutex);
		}
	}
	else
		pthread_mutex_unlock(&args->fork[info->left].mutex);
	return (0);
}

int	eating(t_philo_info *info, t_args *args)
{
	info->last_eat = get_time(0);
	printing(info, args, "is eating");
	if (ft_sleep(info, args, info->last_eat, args->eat_time))
		return (1);
	pthread_mutex_lock(&info->count);
	info->eat_count++;
	pthread_mutex_unlock(&info->count);
	pthread_mutex_lock(&args->fork[info->left].mutex);
	args->fork[info->left].used = 0;
	pthread_mutex_unlock(&args->fork[info->left].mutex);
	pthread_mutex_lock(&args->fork[info->right].mutex);
	args->fork[info->right].used = 0;
	pthread_mutex_unlock(&args->fork[info->right].mutex);
	return (0);
}

int	sleeping(t_philo_info *info, t_args *args)
{
	if (checking(info, args))
		return (1);
	printing(info, args, "is sleeping");
	if (ft_sleep(info, args, get_time(0), args->sleep_time))
		return (1);
	printing(info, args, "is thinking");
	return (0);
}
