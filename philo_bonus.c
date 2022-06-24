/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babkar <babkar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:04:19 by babkar            #+#    #+#             */
/*   Updated: 2022/06/24 12:14:32 by babkar           ###   ########.fr       */
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
	pthread_t	th[2];
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
		data.pid[i] =  p[i].pid_private = id[i] = fork();
        if (id[i] == 0)
        {
			pthread_create(&th[0], NULL, &check_death, p);
			//pthread_create(&th[1], NULL, &trap, p);
			routine(&p[i]);
        }
        i++;
    }
	i = 0;
	while (i < data.nbr)
	{
		waitpid(id[i], &status, 0);
		i++;
	}
}