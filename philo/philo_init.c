/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:50:11 by seohyeki          #+#    #+#             */
/*   Updated: 2024/04/08 20:01:41 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	return (0);
}

int	init_mutex(t_args *args)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&args->printf, NULL) != 0)
		return (1);
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

int	init_philo_info(t_args *args, t_philo_info **philo_info)
{
	int	i;

	i = 0;
	*philo_info = (t_philo_info *)malloc(sizeof(t_philo_info) * (args->philo_num));
	if (!(*philo_info))
		return (1);
	while (i < args->philo_num)
	{
		(*philo_info)[i].id = i + 1;
		(*philo_info)[i].left = i;
		(*philo_info)[i].right = (i + 1) % args->philo_num;
		(*philo_info)[i].eat_count = 0;
		(*philo_info)[i].last_eat = get_time(0);
		(*philo_info)[i].args = args;
		i++;
	}
	return (0);
}
