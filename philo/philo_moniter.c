/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_moniter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:17:42 by seohyeki          #+#    #+#             */
/*   Updated: 2024/04/16 18:23:16 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	all_philo_eat(t_args *args, int *i, int *eat_philo)
{
	if (*eat_philo == args->philo_num)
	{
		pthread_mutex_lock(&args->end);
		args->end_flag = 1;
		pthread_mutex_unlock(&args->end);
		return (1);
	}
	*i = 0;
	*eat_philo = 0;
	return (0);
}

int	monitering(t_args *args, t_philo_info *info)
{
	int	i;
	int	eat_philo;

	i = 0;
	eat_philo = 0;
	while (1)
	{
		pthread_mutex_lock(&args->end);
		if (args->end_flag)
		{
			pthread_mutex_unlock(&args->end);
			break ;
		}
		pthread_mutex_unlock(&args->end);
		pthread_mutex_lock(&info[i].count);
		if (info[i].eat_count >= args->must_eat)
			eat_philo++;
		pthread_mutex_unlock(&info[i].count);
		i++;
		if (i == args->philo_num)
			if (all_philo_eat(args, &i, &eat_philo))
				return (0);
		usleep(10);
	}
	return (0);
}
