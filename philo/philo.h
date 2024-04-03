/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:43:58 by seohyeki          #+#    #+#             */
/*   Updated: 2024/04/03 21:48:36 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	int				philo_num;
	int				alive_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	long			time;
	pthread_mutex_t *fork;
}				t_data;

typedef struct s_philo_data
{
	int	id;
	int	left;
	int	right;
	int	eat_count;
}				t_philo_data;

long long ft_atoi(char *str);

#endif