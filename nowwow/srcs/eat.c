/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonie <wonie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:01:12 by wonie             #+#    #+#             */
/*   Updated: 2023/09/23 16:06:17 by wonie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	mutex(t_list *list, int onoff)
{
	if (onoff == 1)
		pthread_mutex_lock(&(list->fork));
	else if (onoff == 0)
		pthread_mutex_unlock(&(list->fork));
}

t_bool	eveneat_half(t_list *list, int nrd)
{
	mutex(list, 1);
	if (switchoff(list))
	{
		pthread_mutex_unlock(&(list->fork));
		return (1);
	}
	print_act(list, nrd, 0);
	mutex(list->next, 1);
	if (switchoff(list))
	{
		pthread_mutex_unlock(&(list->fork));
		pthread_mutex_unlock(&(list->next->fork));
		return (1);
	}
	print_act(list, nrd, 1);
	return (0);
}

t_bool	eveneat(t_list *list, int nrd)
{
	if (eveneat_half(list, nrd))
		return (1);
	if (status(list, EAT))
		return (1);
	list->info->taken = get_time();
	if (moniterlife(list, list->info->eattime))
	{
		pthread_mutex_unlock(&(list->fork));
		pthread_mutex_unlock(&(list->next->fork));
		return (1);
	}
	mutex(list, 0);
	mutex(list->next, 0);
	if (switchoff(list))
		return (1);
	status(list, SLEEP);
	return (0);
}

t_bool	oddeat_half(t_list *list, int nrd)
{
	mutex(list->next, 1);
	if (switchoff(list))
	{
		pthread_mutex_unlock(&(list->next->fork));
		return (1);
	}
	print_act(list, nrd, 0);
	mutex(list, 1);
	if (switchoff(list))
	{
		pthread_mutex_unlock(&(list->next->fork));
		pthread_mutex_unlock(&(list->fork));
		return (1);
	}
	yield(list);
	print_act(list, nrd, 1);
	return (0);
}

t_bool	oddeat(t_list *list, int nrd)
{
	if (oddeat_half(list, nrd))
		return (1);
	if (status(list, EAT))
		return (1);
	list->info->taken = get_time();
	if (moniterlife(list, list->info->eattime))
	{
		pthread_mutex_unlock(&(list->next->fork));
		pthread_mutex_unlock(&(list->fork));
		return (1);
	}
	mutex(list->next, 0);
	mutex(list, 0);
	if (switchoff(list))
		return (1);
	status(list, SLEEP);
	return (0);
}
