/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuszyns <cbuszyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:19:32 by cbuszyns          #+#    #+#             */
/*   Updated: 2022/11/10 15:01:44 by cbuszyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_data(t_data *data)
{
	if (data->tid)
		free(data->tid);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	clear_data(data);
}

int	ft_error(char *str, t_data *data)
{
	printf("%s", str);
	if (data)
		ft_exit(data);
	return (1);
}

int	alloc(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->num_philo);
	if (!data->tid)
		return (ft_error("Allocation Error: Thread ID", data));
	data->forks = malloc(sizeof(pthread_t) * data->num_philo);
	if (!data->forks)
		return (ft_error("Allocation Error: Forks", data));
	data->philos = malloc(sizeof(pthread_t) * data->num_philo);
	if (!data->philos)
		return (ft_error("Allocation Error: Philos", data));
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	data->philos[0].l_fork = &data->forks[0];
	data->philos[0].r_fork = &data->forks[data->num_philo -1];
	i = 1;
	while (i < data->num_philo)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

void	init_philoss(t_data *data)
{
	int	i;
	while (i < data->num_philo)
	{
		data->philos[i].data = 0;
		data->philos[i].id = i + 1;
		data->philos[i].time_to_die = data->death_time;
		data->philos[i].eat_cont = 0;
		data->philos[i].eating = 0;
		data->philos[i].status = 0;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
}

int	init_data(t_data *data, char **argv, int argc)
{
	data->num_philo = (int) ft_atoi(argv[1]);
	data->death_time = (u_int64_t) ft_atoi(argv[2]);
	data->eat_time = (u_int64_t) ft_atoi(argv[3]);
	data->sleep_time = (uint64_t) ft_atoi(argv[4]);
	if (argc == 6)
		data->num_meals = (int) ft_atoi(argv[5]);
	else
		data->num_meals = -1;
	if (data->num_philo <= 0 || data->num_philo > 200 || data->death_time < 0 || data->eat_time < 0 || data->sleep_time < 0)
		return (-1);
	data->dead = 0;
	data->finished = 0;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	return (0);
}

int	init(t_data *data, char **argv, int argc)
{
	if (init_data(data, argv, argc))
		return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (1);
	init(&data, argv, argc);
}