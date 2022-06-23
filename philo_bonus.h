/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babkar <babkar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:04:22 by babkar            #+#    #+#             */
/*   Updated: 2022/06/22 17:19:14 by babkar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
typedef struct s_shared
{
	int				nbr;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				time_must_eat;
	long long		time_birth;
	int				full;
	sem_t			*semaphore;
	pid_t				*pid;
}	t_shared;

typedef struct s_philo
{
	int				index;
	long long		last_meal;
	int 			pid_private;
	int				check_time_must_eat;
	int				death;
	pthread_t		t;
	t_shared		*data;
}	t_philo;

long long	get_time(void);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_atoi(const char *str);
void		ft_usleep(int time);
int			ft_isdigit(int c);
int			parsing(int ac);
int			puterr(void);
t_philo		*philo_init(t_philo *p, t_shared *data, int ac);
t_shared	init_data(char **av);
void		philo_info(t_philo *p, t_shared *data, int i);
void		*eat(t_philo *p, t_shared *data);
void		*think(t_philo *p, t_shared *data);
void		*ft_sleep(t_philo *p, t_shared *data);
void		*check_time_must_eat(void	*arg);
void		*check_death(void *arg);
#endif
