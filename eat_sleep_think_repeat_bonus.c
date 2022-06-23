/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think_repeat_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babkar <babkar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 20:40:14 by babkar            #+#    #+#             */
/*   Updated: 2022/06/23 15:52:32 by babkar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
sem_t	*lock;


void	kill_child_process(int pid ,t_shared *data, int index)
{
	// int	i;
	// //unlink("lock1");
	lock = sem_open("lock1", O_CREAT, 0);
	// i = 0;
	// while (i < data->nbr)
	// {
	// 	if (data->pid[i] != pid)
	// 	{
	// 		//printf("{{{{{{{{{pid : %d}}}}}}}}}\n",data->pid[i]);
	// 		kill(data->pid[i], SIGKILL);
	// 	}
	// 	i++;
	// }
	//sem_wait(lock);
	//printf("[%05lld] %d is dead\n", get_time() - data->time_birth, index + 1);
	//kill(0, SIGKILL);
	//kill(pid, SIGINT);
	
}
void	*trap(void *arg)
{
	t_philo		*p;
	t_shared	*data;

	p = (t_philo *)arg;
	data = p->data;
	
	//sleep(500);
	exit(0);
	return (NULL);
}

void	*eat(t_philo *p, t_shared *data)
{
	sem_wait(data->semaphore);
	if (p->death || data->full){
		printf("[%05llu] %d is dead\n", get_time() - data->time_birth, p->index + 1);
		exit(1);
	}
	printf("[%05llu] %d has taken a fork\n", get_time() - data->time_birth, p->index + 1);
	sem_wait(data->semaphore);
	if (p->death || data->full)
	{
		printf("[%05llu] %d is dead\n", get_time() - data->time_birth, p->index + 1);
		exit(1);
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
	if (p->death){
		printf("[%05llu] %d is dead\n", get_time() - data->time_birth, p->index + 1);
		exit(1);
		}
	printf("[%05llu] %d is sleeping\n",
		get_time() - data->time_birth, p->index + 1);
	usleep(p->data->time_sleep * 1000);
	return (think(p, data));
}

void	*think(t_philo *p, t_shared *data)
{
	if (p->death){
		printf("[%05llu] %d is dead\n", get_time() - data->time_birth, p->index + 1);
		exit(1);
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
		i++;
		if (data->nbr == i)
			i = 0;
		if (get_time() - p[i].last_meal > data->time_die){
			
			p[i].death = 1;
			//printf("i + 1 = %d\n", i + 1);
			break;
		}
	}
	printf("[%05llu] %d is dead\n", get_time() - data->time_birth, i + 1);
	exit(1);
	//if (p[i].death == 1)
		//kill_child_process(p[i].pid_private, data, i);
	return (NULL);
}