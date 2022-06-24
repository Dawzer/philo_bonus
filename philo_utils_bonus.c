/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babkar <babkar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:39:11 by babkar            #+#    #+#             */
/*   Updated: 2022/06/24 18:18:41 by babkar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == 45)
		sign *= (-1);
	if (*str == 45 || *str == 43)
		str++;
	if (!ft_isdigit(*str))
		return (0);
	while (ft_isdigit(*str))
		num = num * 10 + (*str++ - 48);
	return (num * sign);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*string1;
	unsigned char	*string2;

	string1 = (unsigned char *)s1;
	string2 = (unsigned char *)s2;
	i = 0;
	while (string1[i] == string2[i])
	{
		if (string1[i] == '\0' && string2[i] == '\0')
			return (0);
		i++;
	}
	return (string1[i] - string2[i]);
}

long long	get_time(void)
{
	struct timeval	tv;
	struct timezone	tz;

	gettimeofday(&tv, &tz);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int time)
{
	long long	current_time;

	current_time = get_time();
	while (get_time() - current_time < time)
		;
}

void	ft_print(char *str, t_philo *p, t_shared *data)
{
	sem_wait(p->print);
	if (data->death)
	{
		exit(0);
	}
	printf("[%05llu] %d %s\n", get_time() - p->data->time_birth, p->index + 1, str);
	sem_post(p->print);
}