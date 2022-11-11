/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuszyns <cbuszyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:17:43 by cbuszyns          #+#    #+#             */
/*   Updated: 2022/11/11 16:39:53 by cbuszyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
    struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				eat_cont;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
} t_philo;


typedef struct s_data
{
	pthread_t		*tid;
    int 			num_philo;
    int 			num_meals;
    int 			dead;
    int 			finished;
	t_philo			*philos;
	u_int64_t		death_time;
	u_int64_t		eat_time;
	u_int64_t		sleep_time;
	u_int64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
} t_data;

//philo.c
int	ft_error(char *str, t_data *data);
void	ft_exit(t_data *data);
void	clear_data(t_data *data);

//init.c
int	init(t_data *data, char **argv, int argc);

//utils.c
long	ft_atoi(const char *str);

#endif