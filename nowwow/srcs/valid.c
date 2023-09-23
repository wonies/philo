/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonie <wonie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:01:39 by wonie             #+#    #+#             */
/*   Updated: 2023/09/23 18:08:56 by wonie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static	t_bool	validinput(char *c);

t_bool	validphilo(int ac, char **av)
{
	int		i;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		printf("\033[0;31m❗️Not Valid Input Condition❗️\n");
		return (0);
	}
	while (i < ac)
	{
		if (!(validinput(av[i])))
		{
			printf("\033[0;31m🍉Not Valid Input Condition🍉\n");
			return (0);
		}
		i++;
	}
	return (1);
}

static	t_bool	validinput(char *c)
{
	while (*c)
	{
		if (!(*c >= '0' && *c <= '9') && !(*c == '+'))
			return (0);
		c++;
	}
	return (1);
}

t_bool	validinfo(t_list *list, t_philo *share)
{
	t_bool	valid;

	valid = 1;
	if (list->info->cnt <= 0)
	{
		valid = 0;
		printf("\033[0;31m🍉Philosopher wasnt there🍉\n");
	}
	else if (list->info->lifetime <= 0 || list->info->eattime <= 0 || \
	list->info->naptime <= 0)
	{
		valid = 0;
		printf("\033[0;31m🍉Not valid time🍉\n");
	}
	if (valid == 0)
	{
		free(share);
		free(list->info);
		free(list);
		return (0);
	}
	return (1);
}

t_bool	validzero(int ac, char **av, t_philo *share)
{
	if (ft_atoi(av[1]) == 0)
	{
		printf("\033[0;31m🍉Philosopher wasnt there🍉\n");
		free(share);
		return (0);
	}
	if (ac == 6)
	{
		if (ft_atoi(av[5]) == 0)
		{
			printf("\033[0;31m🍑Option must be over ZER0🍑\n");
			free(share);
			return (0);
		}
	}
	return (1);
}

t_bool	destroy_mutex(t_list *list, int idx)
{
	int	i;

	i = -1;
	if (idx == 0 || idx == 1)
	{
		pthread_mutex_destroy(&(list->share->prints));
		pthread_mutex_destroy(&(list->share->inactive));
		pthread_mutex_destroy(&(list->share->opt));
	}
	if (idx == 0)
	{
		while (++i < list->info->cnt)
		{
			pthread_mutex_destroy(&(list->fork));
			pthread_mutex_destroy(&(list->active));
			list = list->next;
		}
	}
	return (0);
}
