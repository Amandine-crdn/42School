/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerdan <acerdan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 08:04:02 by acerdan           #+#    #+#             */
/*   Updated: 2022/04/18 08:11:20 by acerdan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	ft_last_check(t_data *data, t_philo *philos, int philos_ate)
{
	if (data->args.nb_of_meal > 0 && philos_ate == data->args.nb_of_philo)
	{
		happy_end_print(philos, HAPPY_END);
		data->death = 1;
	}
}

static void	monitoring(t_data *data, t_philo *philos)
{
	int	i;
	int	philos_ate;

	while (!data->death)
	{
		usleep(3000);
		i = 0;
		philos_ate = 0;
		while (i < data->args.nb_of_philo && !data->death)
		{
			pthread_mutex_lock(&philos[i].tamagotchi_meal);
			if (get_time() > philos[i].die_time)
			{
				print_mutex(&philos[i], DIE);
				data->death = 1;
			}
			if (philos[i].count_meals >= data->args.nb_of_meal)
				philos_ate++;
			pthread_mutex_unlock(&philos[i].tamagotchi_meal);
			i++;
		}
		ft_last_check(data, philos, philos_ate);
	}
}

static int	more_philo(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	data->start_program = get_time();
	while (i < data->args.nb_of_philo)
	{
		philos[i].die_time = data->start_program + data->args.time_to_die;
		if (pthread_create(&philos[i].pid_pthread, NULL, &routine, &philos[i]))
			return (1);
		i++;
	}
	monitoring(data, philos);
	i = 0;
	while (i < data->args.nb_of_philo)
	{
		pthread_join(philos[i].pid_pthread, NULL);
		i++;
	}
	return (0);
}

static int	one_philo(t_data *data, t_philo *philo)
{
	data->start_program = get_time();
	philo->die_time = data->start_program + data->args.time_to_die;
	if (pthread_create(&(philo->pid_pthread), NULL, &unique_routine, philo))
		return (1);
	pthread_join(philo->pid_pthread, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philos;

	if (argc < 5 || argc > 6)
		return (write_error(ERROR_NUM_ARGS, 1));
	if (ft_check_errors(argc, argv))
		return (write_error(ERROR_INVALID_ARGS, 1));
	if (ft_init(&data, &philos, argc, argv))
		return (1);
	if (data->args.nb_of_philo == 1)
		one_philo(data, philos);
	else
		more_philo(data, philos);
	ccleaner(data, philos, data->args.nb_of_philo);
	return (0);
}
