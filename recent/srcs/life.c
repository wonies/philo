#include "../inc/philo.h"

t_bool	thread(t_list **list);
t_bool	thread_join(t_list **list);

t_bool	mutex_init(t_list **list)
{
	t_list	*cur = *list;
	int		i;

	i = 0;
	while (i < cur->info->cnt)
	{
		pthread_mutex_init(&cur->fork, NULL);
		// printf("\t\tshow me the seg\n");
		pthread_mutex_init(&cur->active, NULL);
		//printf("\t\tshow me the seg222\n");
		cur = cur->next;
		i++;
		// if (*list == cur)
		// 	break ;
	}
	thread(list);
	return (0);
}

t_bool	thread_join(t_list **list)
{
	t_list	*cur;
	int		i;

	cur = *list;
	i = 0;
	while (i < cur->info->cnt)
	{
		pthread_join(cur->niche, NULL);
		cur =cur->next;
		i++;
		if (*list == cur)
			break ;
	}
	return (0);
}

void	thread_odd(t_list *cur)
{
	int	i = 1;
	while (i < cur->info->cnt)
	{
		printf("starting philo %d\n", i);
		pthread_create(&cur->niche, NULL, &routine, cur);
		i += 2;
		cur = cur->next->next;
	}
}

void	thread_even(t_list *cur)
{
	int	i = 2;
	while (i <= cur->info->cnt)
	{
		printf("starting philo %d\n", i);
		pthread_create(&cur->niche, NULL, &routine, cur);
		i += 2;
		cur = cur->next->next;
	}
	if (cur->info->cnt % 2 != 0)
	{
		printf("starting philo %d\n", i - 1);
		cur = cur->prev;
		usleep(cur->info->eattime * 1000);
		pthread_create(&cur->niche, NULL, &routine, cur);
	}
}

t_bool	thread(t_list **list)
{
	t_list	*cur;
	// int		i;

	cur = *list;
	// pthread_mutex_lock((&(*list)->share->circle));
	//i = 0;
	thread_odd(cur);
	cur = *list;
	thread_even(cur->next);
	cur = *list;
	while (1)
	{
		pthread_mutex_lock(&(cur->active));
		if (cur->info->status == DEATH)
		{
			pthread_mutex_lock(&(cur->share->prints));
			printf("\t\t---------------\t\t\n");
			pthread_mutex_unlock(&(cur->share->prints));
			pthread_mutex_unlock(&(cur->active));
			break ;
		}
		pthread_mutex_unlock(&(cur->active));
	}
	// while (i < cur->info->cnt)
	// {
	// 	if (cur == (*list)->prev && cur->info->cnt % 2 != 0)
	// 	{
	// 		printf("idx: {{%d}}\n", cur->info->idx);
	// 		usleep(cur->info->eattime * 1000);
	// 	}
	// 		// moniterlife(cur->info->eattime + cur->info->eattime + cur->info->naptime);
	// 	pthread_create(&cur->niche, NULL, &routine, cur);
	// 	cur = cur->next;
	// 	i++;
	// 	// if (*list == cur)
	// 	// 	break ;
	// 	// if (*list == cur)
	// 	// {
	// 	// 	cur->share->record += cur->info->lifetime;
	// 	// }
	// }
	// pthread_mutex_unlock((&(*list)->share->circle));
	// (*list)->share->record = get_time();
	// cur = *list;
	// while (1)
	// {
	// 	cur->info->taken = get_time();
	// 	cur = cur->next;
	// 	if (*list == cur)
	// 		break ;
		
	// }
	thread_join(list);
	return (0);
}

t_bool	get_fork(t_list **list)
{
	mutex_init(list);
	return (0);
}
