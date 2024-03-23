/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:10:17 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/23 22:29:14 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *act(void *data)
{
    int id;
    int i = 0;
    id = *((int *)data);

    while(1)
    {
        printf("%d : %d\n", id, i);
        i++;
        sleep(1);
    }
}

int check_invalid_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}

int	init_data(t_data *philo, char **argv)
{
	if (check_invalid_args(argv))
		return (1);
	philo->num_of_philo = (int)ft_atoi(argv[1]);
	philo->time_to_die = (int)ft_atoi(argv[2]);
	philo->time_to_eat = (int)ft_atoi(argv[3]);
	philo->time_to_sleep = (int)ft_atoi(argv[4]);
	philo->must_eat = (int)ft_atoi(argv[5]);
	return (0);
}

int	main(int argc, char **argv)
{
	struct timeval	time;
	t_data			data;
	pthread_t		*philo;
	int				i;
	int				status;

	if (argc != 5 && argc != 6)
		return (1);
	gettimeofday(&time, NULL);
	if (init_data(&data, argv))
		return (1);
	i = 0;
	philo = (pthread_t *)malloc(sizeof(pthread_t) * (data.num_of_philo));
	// pthread_create(&philo[i], NULL, act, &i);
	while (i < data.num_of_philo)
	{
		pthread_create(&philo[i], NULL, act, (void *)&i);
		i++;
	}
	/*출력*/
	// printf("num_of_philo: %d\n", data.num_of_philo);
	// printf("time_to_die: %d\n", data.time_to_die);
	// printf("time_to_eat: %d\n", data.time_to_eat);
	// printf("time_to_sleep: %d\n", data.time_to_sleep);
	// printf("must_eat: %d\n", data.must_eat);
	return (0);
}