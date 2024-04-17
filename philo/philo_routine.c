/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:39:29 by seohyeki          #+#    #+#             */
/*   Updated: 2024/04/18 01:58:39 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

int	take_fork_one(t_philo_info *info, t_args *args)
{
	if (info->id % 2 == 1)
	{
		pthread_mutex_lock(&args->fork[info->left].mutex);
		if (args->fork[info->left].used == 0)
		{
			args->fork[info->left].used = 1;
			pthread_mutex_unlock(&args->fork[info->left].mutex);
			ft_printf(info, args, "has taken a fork");
			return (1);
		}
		pthread_mutex_unlock(&args->fork[info->left].mutex);
	}
	else
	{
		pthread_mutex_lock(&args->fork[info->right].mutex);
		if (args->fork[info->right].used == 0)
		{
			args->fork[info->right].used = 1;
			pthread_mutex_unlock(&args->fork[info->right].mutex);
			ft_printf(info, args, "has taken a fork");
			return (1);
		}
		pthread_mutex_unlock(&args->fork[info->right].mutex);
	}
	return (0);
}

int	take_fork_two(t_philo_info *info, t_args *args)
{
	if (info->id % 2 == 1)
	{
		pthread_mutex_lock(&args->fork[info->right].mutex);
		if (args->fork[info->right].used == 0)
		{
			args->fork[info->right].used = 1;
			pthread_mutex_unlock(&args->fork[info->right].mutex);
			ft_printf(info, args, "has taken a fork");
			return (1);
		}
		pthread_mutex_unlock(&args->fork[info->right].mutex);
	}
	else
	{
		pthread_mutex_lock(&args->fork[info->left].mutex);
		if (args->fork[info->left].used == 0)
		{
			args->fork[info->left].used = 1;
			pthread_mutex_unlock(&args->fork[info->left].mutex);
			ft_printf(info, args, "has taken a fork");
			return (1);
		}
		pthread_mutex_unlock(&args->fork[info->left].mutex);
	}
	return (0);
}

int	eating(t_philo_info *info, t_args *args)
{
	info->last_eat = get_time(0);
	ft_printf(info, args, "is eating");
	if (ft_usleep(info, args, info->last_eat, args->eat_time))
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
	ft_printf(info, args, "is sleeping");
	if (ft_usleep(info, args, get_time(0), args->sleep_time))
		return (1);
	ft_printf(info, args, "is thinking");
	return (0);
}

void	routine(t_philo_info *info, t_args *args)
{
	while (check_end(info, args) == 0)
	{
		if (take_fork_one(info, args))
		{
			while (check_end(info, args) == 0)
			{
				if (take_fork_two(info, args))
					break ;
			}
			if (eating(info, args))
				break ;
			if (sleeping(info, args))
				break ;
			usleep(args->usleep_time);
		}
		usleep(args->usleep_time);
	}
}
