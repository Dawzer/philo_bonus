/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babkar <babkar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:04:19 by babkar            #+#    #+#             */
/*   Updated: 2022/06/24 19:35:08 by babkar           ###   ########.fr       */
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
	eat(p, data);
	return (NULL);
}

int main(int ac, char **av)
{
	t_philo		*p;
	t_shared	data;
	int			i;
	pthread_t	th[2];
	int			*id;
	
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
			pthread_create(&th[1], NULL, &trap, p);
			routine(&p[i]);
			exit (0);
        }
        i++;
    }
	i = 0;
	while (i < data.nbr)
	{
		waitpid(id[i], NULL, 0);
		i++;
	}
}