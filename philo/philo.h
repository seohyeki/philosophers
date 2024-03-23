/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:43:58 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/23 16:26:55 by seohyeki         ###   ########.fr       */
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
	int	num_of_philo; //The number of philosophers and also the number of forks
	int	time_to_die; //If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die
	int	time_to_eat; //The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
	int	time_to_sleep; //The time a philosopher will spend sleeping
	int	must_eat; // If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. 
	int	d_flag; //die flag
}				t_data;

typedef struct s_philo
{
	int	last_eat_time; //가장 마지막으로 먹기 시작한 시간
	int	eat_count;
}				t_philo;

long long ft_atoi(char *str);
void	*philo_routine(t_philo *philo);

#endif