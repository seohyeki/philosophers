/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:30:18 by seohyeki          #+#    #+#             */
/*   Updated: 2024/04/17 18:39:17 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

long long	ft_atoi(char *str)
{
	long long	num;

	num = 0;
	if (str == 0)
		return (-1);
	while (*str)
	{
		if (*str < '0' || '9' < *str)
			return (-1);
		num = num * 10 + *str - '0';
		if (num > 2147483647)
			return (-1);
		str++;
	}
	return (num);
}

long	get_time(long t)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - t);
}

int	ft_usleep(t_philo_info *info, t_args *args, long cur, int act_time)
{
	while (check_end(info, args) == 0)
	{
		if (get_time(cur) >= act_time)
			return (0);
		usleep(150);
	}
	return (1);
}

void	ft_printf(t_philo_info *info, t_args *args, char *msg)
{
	pthread_mutex_lock(&args->printf);
	pthread_mutex_lock(&args->end);
	if (args->end_flag == 0)
		printf("%ld %d %s\n", get_time(args->start_time), info->id, msg);
	pthread_mutex_unlock(&args->end);
	pthread_mutex_unlock(&args->printf);
}
