/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think_repeat_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babkar <babkar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 20:40:14 by babkar            #+#    #+#             */
/*   Updated: 2022/06/24 19:35:14 by babkar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
sem_t	*lock;

void	*trap(void *arg)
{
	t_philo		*p;
	t_shared	*data;

	p = (t_philo *)arg;
	data = p->data;
	sem_wait(data->trap);
	sem_post(data->trap);
	exit(0);
}

void	*eat(t_philo *p, t_shared *data)
{
	sem_wait(data->semaphore);
	ft_print("has taken a fork", p, data);
	sem_wait(data->semaphore);
	ft_print("has taken a fork", p, data);
	ft_print("is eating", p, data);
	p->last_meal = get_time();
	if (p->check_time_must_eat < data->time_must_eat)
		p->check_time_must_eat += 1;
	ft_usleep(data->time_eat);
	sem_post(data->semaphore);
	sem_post(data->semaphore);
	return (ft_sleep(p, data));
}

void	*ft_sleep(t_philo *p, t_shared *data)
{
	ft_print("is sleeping", p, data);
	ft_usleep(data->time_sleep);
	return (think(p, data));
}

void	*think(t_philo *p, t_shared *data)
{
	ft_print("is thinking", p, data);
	return (eat(p, data));
}

void	*check_death(void *arg)
{
	t_philo		*p;
	t_shared	*data;
	int			i;
	int			count;

	count = 0;
	i = 0;
	p = (t_philo *)arg;
	data = p->data;
	while (1)
	{
		if (get_time() - p[i].last_meal > data->time_die){
			sem_wait(data->protect);
			printf("[%05llu] %d died\n", get_time() - data->time_birth, i + 1);
			data->death = 1;
			sem_post(data->trap);
			exit(0);
		}
		i++;
		if (data->nbr == i)
			i = 0;
	}
	return (NULL);
}