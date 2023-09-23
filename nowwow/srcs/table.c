/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonie <wonie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:01:31 by wonie             #+#    #+#             */
/*   Updated: 2023/09/23 17:42:16 by wonie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static t_bool	think(t_list *list, int nrd)
{
	if (switchoff(list))
		return (1);
	print_act(list, nrd, 3);
	if (list->info->cnt % 2 == 0)
	{
		if (moniterlife(list, (list->info->eattime - list->info->naptime) * \
		(list->info->eattime >= list->info->naptime)))
			return (1);
	}
	else
	{
		if (moniterlife(list, \
		((list->info->eattime * 2 - list->info->naptime)) * \
		(list->info->eattime >= list->info->naptime)))
			return (1);
	}
	return (0);
}

static	t_bool	sleeps(t_list *list, int nrd)
{
	if (switchoff(list))
		return (1);
	print_act(list, nrd, 2);
	pthread_mutex_unlock(&(list->share->prints));
	if (moniterlife(list, list->info->naptime))
		return (1);
	if (switchoff(list))
		return (1);
	status(list, STARVE);
	return (0);
}

t_bool	eat(t_list *list, int nrd)
{
	if (nrd % 2 != 0)
	{
		if (oddeat(list, nrd))
			return (1);
	}
	else
	{
		if (eveneat(list, nrd))
			return (1);
	}
	if (sleeps(list, nrd))
		return (1);
	return (0);
}

void	table(t_list *list, int nrd)
{
	if (list->info->cnt == 1)
	{
		pthread_mutex_lock(&(list->share->prints));
		printf("\033[0;32m%llu %d has taken a fork\n", \
		get_time() - list->info->taken, list->info->idx);
		pthread_mutex_unlock(&(list->share->prints));
		moniterlife(list, list->info->lifetime);
		return ;
	}
	while (1)
	{
		if (eat(list, nrd))
			return ;
		if (think(list, nrd))
			return ;
	}
}

void	*routine(void *arg)
{
	t_list	*list;

	list = (t_list *)arg;
	table(list, list->info->idx);
	return (NULL);
}
