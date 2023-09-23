/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eatutil.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonie <wonie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:01:19 by wonie             #+#    #+#             */
/*   Updated: 2023/09/23 17:07:28 by wonie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static	t_status	ref_stat(t_list *list)
{
	t_status	result;

	pthread_mutex_lock(&list->active);
	result = list->info->status;
	pthread_mutex_unlock(&list->active);
	return (result);
}

t_bool	yield(t_list *list)
{
	if (ref_stat(list->prev) == STARVE && ref_stat(list->next) == SLEEP)
	{
		mutex(list, 0);
		usleep(500);
		mutex(list, 1);
		return (1);
	}
	return (0);
}
