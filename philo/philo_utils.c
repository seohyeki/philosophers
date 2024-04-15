/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:30:18 by seohyeki          #+#    #+#             */
/*   Updated: 2024/04/16 01:26:50 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

static int	ft_isdigit(char c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

long long	ft_atoi(char *str)
{
	long long	num;

	num = 0;
	if (str == 0)
		return (-1);
	while (*str)
	{
		if (!ft_isdigit(*str))
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

int	ft_sleep(t_philo_info *info, t_args *args, int act_time)
{
	long	start_time;

	start_time = get_time(0);
	while (1)
	{
		if (checking(info, args))
			return (1);
		else if (get_time(0) - start_time >= act_time)
			break ;
		usleep(100);
	}
	return (0);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	if (s1 == s2 || n == 0)
		return (0);
	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((str1[i] == str2[i]) && (i + 1 < n))
		i++;
	return (str1[i] - str2[i]);
}
