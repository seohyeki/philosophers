/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:10:17 by seohyeki          #+#    #+#             */
/*   Updated: 2024/04/08 20:35:33 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

long	get_time(long t)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - t);
}

void *act1(void *arg)
{
	t_philo_info *info = (t_philo_info *)arg;
	t_args	*args = info->args;

	pthread_mutex_lock(&args->fork[info->left]);
	
	pthread_mutex_lock(&args->printf);
	printf("%ld %d has taken a fork\n", get_time(args->start), info->id);
	pthread_mutex_unlock(&args->printf);
	
	pthread_mutex_lock(&args->fork[info->right]);
	
	pthread_mutex_lock(&args->printf);
	printf("%ld %d has taken a fork\n", get_time(args->start), info->id);
	pthread_mutex_unlock(&args->printf);
	
	pthread_mutex_lock(&args->printf);
	printf("%ld %d is eating\n", get_time(args->start), info->id);
	pthread_mutex_unlock(&args->printf);
	
	usleep(args->eat_time * 1000);
	
	pthread_mutex_unlock(&args->fork[info->left]);
	pthread_mutex_unlock(&args->fork[info->right]);
	return (0);
}

void *act2(void *arg)
{
	t_philo_info *info = (t_philo_info *)arg;
	t_args	*args = info->args;
	long	ms;

	usleep(10);
	pthread_mutex_lock(&args->fork[info->right]);
	
	pthread_mutex_lock(&args->printf);
	ms = get_time(args->start);
	printf("%ld %d has taken a fork\n", ms, info->id);
	pthread_mutex_unlock(&args->printf);
	
	pthread_mutex_lock(&args->fork[info->left]);

	pthread_mutex_lock(&args->printf);
	printf("%ld %d has taken a fork\n", get_time(args->start), info->id);
	pthread_mutex_unlock(&args->printf);
	
	pthread_mutex_lock(&args->printf);
	printf("%ld %d is eating\n", get_time(args->start), info->id);
	pthread_mutex_unlock(&args->printf);

	usleep(args->eat_time * 1000);

	pthread_mutex_unlock(&args->fork[info->right]);
	pthread_mutex_unlock(&args->fork[info->left]);
	return (0);
}

int	main(int argc, char **argv)
{
	t_args			args;
	t_philo_info	*info;
	pthread_t		*philo;
	int				i;

	if (argc != 5 && argc != 6)
		return (1);
	if (init_args(&args, argc, argv))
		return (1);
	if (init_philo_info(&args, &info))
		return (1);
	if (init_mutex(&args)) //free philo_data, mutex intit 실패시 free fork
		return (1);
	args.start = get_time(0);
	//thread create
	philo = (pthread_t *)malloc(sizeof(pthread_t) * (args.philo_num));
	i = 0;
	while (i < args.philo_num)
	{
		if (i % 2 == 0)
			pthread_create(&philo[i], NULL, act1, &info[i]);
		else
			pthread_create(&philo[i], NULL, act2, &info[i]);
		i++;
	}
	//thread finish(pthread_mutex_destroy도 하기)
	i = 0;
	while (i < args.philo_num)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
	return (0);
}
