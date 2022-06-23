/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babkar <babkar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:04:19 by babkar            #+#    #+#             */
/*   Updated: 2022/06/23 14:38:05 by babkar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

#define sem_name "fork"

sem_t *chopstick;

void	*routine(void *arg)
{
	t_philo		*p;
	t_shared	*data;

	p = (t_philo *)arg;
	data = p->data;
	return (eat(p, data));
	return (NULL);
}
void	routine_2(sem_t **sem)
{
	sem_wait(*sem);
	printf("Entred\n");
	sleep(2);
	printf("Just exiting\n");
	sem_post(*sem);
}
int main(int ac, char **av)
{
	t_philo		*p;
	t_shared	data;
	int			i;
	pthread_t	th;
	sem_t		*sem;
	int			*id;
	int	status;
	
	printf("pid : %d\n",getpid());
	if (!parsing(ac))
		return (puterr());
	p = NULL;
	data = init_data(av);
	p = philo_init(p, &data, ac);
	i = 0;
	id = malloc(data.nbr * sizeof(int));
    while (i < data.nbr)
    {
        //data.pid[i] = fork();
		//p[i].pid_private = fork();
		data.pid[i] =  p[i].pid_private = id[i] = fork();
        if (id[i] == 0)
        {
			pthread_create(&th, NULL, &check_death, p);
			routine(&p[i]);
			//pthread_join(th, NULL);
			//return (i);
        }
        i++;
    }
	i = 0;
	while (i < data.nbr)
	{
		waitpid(id[i], &status, 0);
		//printf("status%d\n", status);
		// if (status)
		// {
		// 	i = 0;
		// 	while (i < data.nbr)
		// 		kill(data.pid[i++], SIGKILL);
		// 	return (0);
		// }
		i++;
	}
	//printf("hi status%d\n", status);
}