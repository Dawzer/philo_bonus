/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babkar <babkar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:39:03 by babkar            #+#    #+#             */
/*   Updated: 2022/06/23 14:04:58 by babkar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_shared	init_data(char **av)
{
	t_shared		data;
	pthread_mutex_t	*fork;
	int				i;

	data.nbr = ft_atoi(av[1]);
	data.time_die = ft_atoi(av[2]);
	data.time_eat = ft_atoi(av[3]);
	data.time_sleep = ft_atoi(av[4]);
	data.time_must_eat = -1;
	if (av[5])
		data.time_must_eat = ft_atoi(av[5]);
	data.time_birth = get_time();
	sem_unlink("fork");
	data.semaphore = sem_open("fork", O_CREAT, 0660, data.nbr);
	data.pid = (int *)malloc(data.nbr * sizeof(int));
	if (!data.pid)
		return (data);
	//i = -1;
	//while (i++ < data.nbr)
	//	data.pid[i] = i;
	data.full = 0;
	return (data);
}

t_philo	*philo_init(t_philo *p, t_shared *data, int ac)
{
	int	i;
	int	size;

	i = 0;
	size = data->nbr + 1;
	if (ac == 6)
		size++;
	p = (t_philo *)malloc(size * sizeof(t_philo));
	if (!p)
		return (NULL);
	while (i < size)
	{
		p[i].data = data;
		p[i].index = i;
		p[i].last_meal = get_time();
		p[i].check_time_must_eat = 0;
		p[i].t = NULL;
		p[i].pid_private = 0;
		p[i].death = 0;
		i++;
	}
	return (p);
}
