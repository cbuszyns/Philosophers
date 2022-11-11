/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuszyns <cbuszyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:19:32 by cbuszyns          #+#    #+#             */
/*   Updated: 2022/11/11 16:47:36 by cbuszyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	input_check(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j])
			{
				j++;
				continue;
			}
			if ((argv[i][j] < 48 || argv[i][j] >57))
				return(ft_error("invalid input", NULL));
			j++;
		}
		i++;
	}
	return (0);
}

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

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (1);
	if (input_check(argv))
		return (1);
	if (init(&data, argv, argc))
		return (1);
}