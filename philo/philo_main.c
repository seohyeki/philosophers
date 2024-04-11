/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:10:17 by seohyeki          #+#    #+#             */
/*   Updated: 2024/04/11 22:28:48 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *acting(void *arg)
{
	t_philo_info *info = (t_philo_info *)arg;
	t_args	*args = info->args;

	if (args->philo_num == 1)
	{
		printing(info, args, "has taken a fork");
		if (ft_sleep(info, get_time(0), args->eat_time))
			return (0);
	}
	if (info->id % 2 == 0)
		usleep(100);
	while (info->end_flag == 0)
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
				info->last_eat = get_time(0);
				printing(info, args, "is eating");
				if (ft_sleep(info, get_time(0), args->eat_time))
					return (0);
				pthread_mutex_lock(&args->fork[info->left].mutex);
				args->fork[info->left].used = 0;
				pthread_mutex_unlock(&args->fork[info->left].mutex);
				pthread_mutex_lock(&args->fork[info->right].mutex);
				args->fork[info->right].used = 0;
				pthread_mutex_unlock(&args->fork[info->right].mutex);
				printing(info, args, "is sleeping");
				if (ft_sleep(info, get_time(0), args->eat_time))
					return (0);
				printing(info, args, "is thinking");
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
	}
	return (0);
}

int	monitering(t_args *args, t_philo_info *info)
{
	int		i;
	int		j;
	long	live;
	
	i = 0;
	while(1)
	{
		live = get_time(0) - info[i].last_eat;
		if (args->alive_time - live <= 0)
		{
			info[i].end_flag = 1;
			j = 0;
			while (j < args->philo_num)
			{
				info[j].end_flag = 1;
				j++;
			}
			printing(&info[i], args, "died");
			return (0);
		}
		i++;
		if (i == args->philo_num)
			i = 0;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_args			args;
	t_philo_info	*info;
	pthread_t		*philo;
	int				i;

	if ((argc != 5 && argc != 6)
		|| init_args(&args, argc, argv) || init_philo_info(&args, &info))
		return (1);
	if (init_mutex(&args)) //free: t_phlio_info *philo
		return (1);
	philo = (pthread_t *)malloc(sizeof(pthread_t) * (args.philo_num));
	if (!philo)
		return (1);
	i = 0;
	while (i < args.philo_num)
	{
		pthread_create(&philo[i], NULL, acting, &info[i]);
		i++;
	}
	monitering(&args, info);
	i = 0;
	while (i < args.philo_num)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
	return (0);
}
