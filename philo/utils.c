/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.ma>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 23:07:45 by aben-nei          #+#    #+#             */
/*   Updated: 2023/07/11 06:06:30 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_philo(t_philo *philo)
{
	t_philo	*tmp;
	int		i;

	i = 0;
	while (philo)
	{
		i++;
		if (i == philo->info->nb_philo)
			break ;
		tmp = philo->next;
		free(philo);
		philo = tmp;
	}
}

bool	check_if_all_eat(t_philo *philo, int i, t_info *info)
{
	while (i > 0)
	{
		pthread_mutex_lock(&philo->must_eat_mutex);
		if (philo->num_of_eat < info->must_eat)
		{
			pthread_mutex_unlock(&philo->must_eat_mutex);
			return (false);
		}
		pthread_mutex_unlock(&philo->must_eat_mutex);
		philo = philo->next;
		i--;
	}
	return (true);
}

void	ft_print(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->print_mutex);
	pthread_mutex_lock(&philo->check_dead);
	if (!philo->is_dead)
	{
		printf("\033[0;36mtime %ld philo %ld \033[0m%s",
			ft_get_time() - philo->start_time, philo->id, str);
	}
	pthread_mutex_unlock(&philo->check_dead);
	pthread_mutex_unlock(&philo->info->print_mutex);
}

int	ft_usleep(long long time)
{
	long long	start;

	start = ft_get_time();
	while (ft_get_time() - start < time)
		usleep(100);
	return (1);
}

long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
