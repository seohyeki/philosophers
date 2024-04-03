/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:10:17 by seohyeki          #+#    #+#             */
/*   Updated: 2024/04/03 21:48:37 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>

long	get_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void *act(void *args)
{
	t_philo_data data = *(t_philo_data *)args;;
	printf("Thread %d\n", data.id);
	printf("Thread %d left fork is %d\n", data.id, data.left);
	printf("Thread %d right fork is %d\n", data.id, data.right);
	return (0);
}

int	init_args(t_data *args, int argc, char **argv)
{
	struct timeval start;
	
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
	args->time = get_time();
	return (0);
}

int init_mutex(t_data *args)
{
	int	i;
	
	i = 0;
	args->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (args->philo_num));
	if (!args->fork)
		return (1);
	while (i < args->philo_num)
	{
		if (pthread_mutex_init(&args->fork[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int init_philo(t_data *args, t_philo_data **philo)
{
	int	i;
	
	i = 0;
	*philo = (t_philo_data *)malloc(sizeof(t_philo_data) * (args->philo_num));
	if (!(*philo))
		return (1);
	while (i < args->philo_num)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].left = i;
		(*philo)[i].right = (i + 1) % args->philo_num;
		(*philo)[i].eat_count = 0;
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			args;
	t_philo_data	*philo_data;
	pthread_t		*philo;
	int				i;

	if (argc != 5 && argc != 6)
		return (1);
	if (init_args(&args, argc, argv))
		return (1);
	if (init_philo(&args, &philo_data)) //malloc 실패
		return (1);
	if (init_mutex(&args)) //malloc 실패 혹은 mutex intit 실패
		return (1);
	printf("time %ld\n", args.time);
	//thread create
	philo = (pthread_t *)malloc(sizeof(pthread_t) * (args.philo_num));
	i = 0;
	while (i < args.philo_num)
	{
		pthread_create(&philo[i], NULL, act, &philo_data[i]);
		i++;
	}
	//thread 끝나는거 확인
	i = 0;
	while (i < args.philo_num)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
	return (0);
}
