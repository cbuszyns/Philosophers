/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuszyns <cbuszyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:48:01 by cbuszyns          #+#    #+#             */
/*   Updated: 2022/11/22 15:07:48 by cbuszyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*supervisor(void *philo_pointer)
{

}

void	*monitor(void *data_pointer)
{

}

void	*routine(void *philo_pointer)
{
	t_philo *philo;

	philo = (t_philo *) philo_pointer;
	philo->time_to_die = philo->data->death_time + get_time();
	if (pthread_create(&philo->t1, NULL, &supervisor, (void *)philo))
		return ((void *)1);
	while (philo->data->dead == 0)
	{
		eat(philo);
		message(THINKING, philo);
	}
	if (pthread_join(philo->t1, NULL))
		return ((void *)1);
	return ((void *)0);
}

int	thread_init(t_data *data)
{
	int			i;
	pthread_t	t0;

	i = -1;
	data->start_time = get_time();
	if (data->num_meals > 0)
	{
		if (pthread_create(&t0, NULL, &monitor, &data->philos[0]))
			return (ft_error(TH_ERR, data));
	}
	while (++i < data->num_philo)
	{
		if(pthread_create(data->tid[i], NULL, &routine, &data->philos[i]))
			return (ft_error(TH_ERR, data));
		ft_usleep(1);
	}
	i = -1;
	while (++i < data->num_philo)
	{
		if (pthread_join(data->tid[i], NULL))
			return (ft_error(JOIN_ERR, data));
	}
	return (0);
}