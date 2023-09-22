#include "../inc/philo.h"


void	f()
{
	system("leaks philo");
}

t_bool	destroy_mutex(t_list *list)
{
	int	i;
	
	i = -1;
	pthread_mutex_destroy(&(list->share->prints));
	pthread_mutex_destroy(&(list->share->inactive));
	while (++i < list->info->cnt)
	{
		pthread_mutex_destroy(&(list->fork));
		pthread_mutex_destroy(&(list->active));
		list = list->next;
	}
	return (0);
}

void	freeres(t_list **list)
{
	t_list	*cur;
	t_list	*rec;
	t_list	*tmp;

	rec = (*list);
	cur = (*list);
	while (cur)
	{
		tmp = cur;
		free(tmp->info);
		free(tmp);
		free(tmp->share);
		cur = cur->next;
		if (cur == rec)
			break ;
	}
	*list = NULL;
}


int	main(int ac, char **av)
{
	t_list	*list;

	list = NULL;
	// atexit(f);
	if (!(validphilo(ac, av)) || !(put_info(ac, av, &list)))
		return (1);
	to_mutex(&list);
	destroy_mutex(list);
	freeres(&list);
}

//green \033[0;32m
//black \033[0;30m
//red \033[0;31m