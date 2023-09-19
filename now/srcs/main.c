#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_list	*list;
	(void)ac;
	int i = -1;

	list = NULL;
	printf("\tPHILO START\n");
	if (init_philo(ac, av, &list) == FALSE)
		return (1);
	printf("\tGET FORK\n");
	get_fork(&list);
	
	pthread_mutex_destroy(&(list->share->prints));
	pthread_mutex_destroy(&(list->share->inactive));
	while (++i < list->info->cnt)
	{
		pthread_mutex_destroy(&(list->fork));
		pthread_mutex_destroy(&(list->active));
		list = list->next;
	}
	// free(*list.info);
	return (0);
}
