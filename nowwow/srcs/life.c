/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonie <wonie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:01:24 by wonie             #+#    #+#             */
/*   Updated: 2023/09/23 18:16:50 by wonie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_bool	thread(t_list **list);

t_bool	to_mutex(t_list **list)
{
	t_list	*cur;
	int		i;

	i = 0;
	cur = *list;
	while (i < cur->info->cnt)
	{
		if (pthread_mutex_init(&cur->fork, NULL) != 0 || \
		pthread_mutex_init(&cur->active, NULL) != 0)
		{
			while (cur)
			{
				pthread_mutex_destroy(&((*list)->fork));
				pthread_mutex_destroy(&((*list)->active));
				cur = cur->prev;
				if (cur == *list)
					return (0);
			}
		}
		cur = cur->next;
		i++;
	}
	thread(list);
	return (1);
}

static t_bool	thread_join(t_list **list)
{
	t_list	*cur;
	int		i;

	cur = *list;
	i = 0;
	while (i < cur->info->cnt)
	{
		pthread_join(cur->niche, NULL);
		cur = cur->next;
		i++;
	}
	return (0);
}

static void	thread_odd(t_list *cur)
{
	int	i;

	i = 1;
	if (cur->info->cnt == 1)
	{
		pthread_create(&cur->niche, NULL, &routine, cur);
		return ;
	}
	while (i < cur->info->cnt)
	{
		pthread_create(&cur->niche, NULL, &routine, cur);
		i += 2;
		cur = cur->next->next;
	}
}

static void	thread_even(t_list *cur)
{
	int	i;

	i = 2;
	while (i <= cur->info->cnt)
	{
		pthread_create(&cur->niche, NULL, &routine, cur);
		i += 2;
		cur = cur->next->next;
	}
	if (cur->info->cnt > 1 && cur->info->cnt % 2 != 0)
	{
		cur = cur->prev;
		usleep(cur->info->eattime * 1000);
		pthread_create(&cur->niche, NULL, &routine, cur);
	}
}

t_bool	thread(t_list **list)
{
	t_list	*cur;

	cur = *list;
	thread_odd(cur);
	cur = *list;
	thread_even(cur->next);
	while (1)
	{
		pthread_mutex_lock(&(cur->share->inactive));
		if (cur->share->dead == 1)
		{
			pthread_mutex_unlock(&(cur->share->inactive));
			break ;
		}
		pthread_mutex_unlock(&(cur->share->inactive));
		cur = cur->next;
	}
	thread_join(list);
	return (1);
}
