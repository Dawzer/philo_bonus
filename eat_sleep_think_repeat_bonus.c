/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think_repeat_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babkar <babkar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 20:40:14 by babkar            #+#    #+#             */
/*   Updated: 2022/06/24 12:37:45 by babkar           ###   ########.fr       */
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
	return (NULL);
}

void	*eat(t_philo *p, t_shared *data)
{
	sem_wait(data->semaphore);
	if (data->death){
		sem_wait(data->protect);
		printf("[%05llu] %d is dead\n", get_time() - data->time_birth, p->index + 1);

		exit(0);
	}
	printf("[%05llu] %d has taken a fork\n", get_time() - data->time_birth, p->index + 1);
	sem_wait(data->semaphore);
	if (data->death)
	{
		sem_wait(data->protect);
		printf("[%05llu] %d is dead\n", get_time() - data->time_birth, p->index + 1);

		exit(0);
	}
	printf("[%05llu] %d has taken a fork\n",get_time() - data->time_birth, p->index + 1);
	printf("[%05llu] %d is eating\n",get_time() - data->time_birth, p->index + 1);
	p->last_meal = get_time();
	if (p->check_time_must_eat < data->time_must_eat)
		p->check_time_must_eat += 1;
	usleep(data->time_eat * 1000);
	sem_post(data->semaphore);
	sem_post(data->semaphore);
	return (ft_sleep(p, data));
}

void	*ft_sleep(t_philo *p, t_shared *data)
{
	if (data->death){
		sem_wait(data->protect);
		printf("[%05llu] %d is dead\n", get_time() - data->time_birth, p->index + 1);
		exit(0);
		}
	printf("[%05llu] %d is sleeping\n",
		get_time() - data->time_birth, p->index + 1);
	usleep(p->data->time_sleep * 1000);
	return (think(p, data));
}

void	*think(t_philo *p, t_shared *data)
{
	if (data->death){
		sem_wait(data->protect);
		printf("[%05llu] %d is dead\n", get_time() - data->time_birth, p->index + 1);
		exit(0);
	}
	printf("[%05llu] %d is thinking\n",
		get_time() - p->data->time_birth, p->index + 1);
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
		//sem_wait(data->counter);
		i++;
		if (get_time() - p[i].last_meal > data->time_die){
			data->death = 1;
			//sem_wait(data->protect);
			//printf("[%05llu] %d is dead\n", get_time() - data->time_birth, i);
			break;
		}
		if (data->nbr == i)
			i = 1;
		//sem_post(data->counter);
	}
	//sem_post(data->trap);
	exit(0);
	return (NULL);
}