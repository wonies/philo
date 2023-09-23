/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonie <wonie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:01:34 by wonie             #+#    #+#             */
/*   Updated: 2023/09/23 18:31:57 by wonie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

ULL	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

t_bool	moniterlife(t_list *list, ULL times)
{
	ULL	cur;
	ULL	lasteat;

	(void)list;
	cur = get_time();
	lasteat = list->info->taken;
	while (1)
	{
		if (died(list, lasteat))
			return (1);
		if (get_time() - cur >= times)
			break ;
		usleep(256);
	}
	return (0);
}

t_bool	died(t_list *list, ULL timz)
{
	ULL	lives;

	lives = list->info->lifetime;
	if (get_time() - timz >= lives)
	{
		pthread_mutex_lock(&(list->share->inactive));
		if (list->share->dead == 0)
		{
			list->share->dead = 1;
			pthread_mutex_lock(&(list->share->prints));
			printf("\033[0;31m%llu %d is died\033[0;30m\n", \
			get_time() - list->share->record, list->info->idx);
			pthread_mutex_unlock(&(list->share->prints));
		}
		pthread_mutex_unlock(&(list->share->inactive));
		return (1);
	}
	return (0);
}
