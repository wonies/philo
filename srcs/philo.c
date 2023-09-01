#include "incs/philo.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

t_bool init_philo(t_philo *philo, char **av)
{
	int	i;
	t_list *list = NULL;
	t_list *new;

	i = 1;
	while (i < 6)
	{
		if (!av[i])
			return (FALSE);
		i++;
	}
	i = 0;
	(*philo).info = malloc(sizeof(t_info));
	if (!((*philo).info))
		return (FALSE);	
	(*philo).info->num = ft_atoi(av[1]);
	while (i++ < (*philo).info->num)
	{
		new = ft_lstnew();
		ft_lstadd_back(&list, new);
	}
	printf("list size: %d\n", ft_lstsize(list));

	(*philo).info->die = ft_atoi(av[2]);
	(*philo).info->eat = ft_atoi(av[3]);
	(*philo).info->sleep = ft_atoi(av[4]);
	(*philo).info->eattime = ft_atoi(av[5]);

	return (TRUE);
}

t_bool get_fork(t_philo *philo)
{
	pthread_mutex_init(&(*philo).mutex, NULL);
	pthread_create(&thread, NULL, thread_routine, &mutex);
}


int main(int ac, char **av)
{
	t_philo philo;
	(void)ac;

	if (!init_philo(&philo, av))
		return (1);
	get_fork(&philo);
	
	free(philo.info);
	return 0;
}

