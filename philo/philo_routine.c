/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:39:29 by seohyeki          #+#    #+#             */
/*   Updated: 2024/04/11 21:19:22 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

void	printing(t_philo_info *info, t_args *args, char *msg)
{
	pthread_mutex_lock(&args->printf);
	if (info->end_flag == 0 || ft_memcmp(msg, "died", 5) == 0)
		printf("%ld %d %s\n", get_time(args->start), info->id, msg);
	pthread_mutex_unlock(&args->printf);
}
