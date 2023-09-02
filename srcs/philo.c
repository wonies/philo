#include "incs/philo.h"
#define MAX_PHILOSOPHERS 1000

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

t_bool init_philo(t_philo *philo, char **av, t_list *list)
{
	int	i;
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
	// if (!((*philo).info))
	// 	return (FALSE);	
	(*philo).info->num = ft_atoi(av[1]);
	while (i < (*philo).info->num)
	{
		printf("count: %d\n", i);
		new = ft_lstnew((*philo).info->num);
		ft_lstadd_back(&list, new);
		i++;
	}
	(*philo).info->die = ft_atoi(av[2]);
	(*philo).info->eat = ft_atoi(av[3]);
	(*philo).info->sleep = ft_atoi(av[4]);
	(*philo).info->eattime = ft_atoi(av[5]);

	return (TRUE);
}

void	*routine(void *arg)
{
	t_list *list = arg;

	printf("Enter------\n");
	// list->niche = pthread_self();
	printf("--------\n");
	printf("\town tid : %d \n", list->index);
	if (list->flag == 0)
		printf("\t %d : philosopher is eating\n", list->index);
	else
	{
		if (list->not_eat == 0)
		{
			printf("\t %d : philosopher is thinking\n", list->index);
			list->not_eat = 1;
			list->flag = 0;
		}
		else
		{
			printf("\t %d : philosopher is sleeping\n", list->index);
			list->not_eat = 0;
			list->flag = 0;
		}
	}
	return NULL;
}

t_bool get_fork(t_list *list)
{	
	int i = 0;
	// pthread_t threads[MAX_PHILOSOPHERS];
	
	printf("\tEnter get_fork func\n");
	int size = ft_lstsize(list) - 1;
	printf("size is : %d\n", size);
	printf("list index : %d\n", list->index);
	while (i < size)
	{
		list[i].index = i + 1;
		printf("\tindex ; %d\n", list->index);
		if ((i + 1) % 2 == 0)
			list->flag = 0;
		else
			list->flag = 1;
		printf("\tmutex init\n");
		pthread_mutex_init(&list[i].fork, NULL);
		printf("Enter 2 -----\n");
		pthread_create(&list[i].niche, NULL, &routine, &list[i]);
		// threads[i] = list[i].niche;
		pthread_detach(list[i].niche);
		i++;
	}

	i = 0;
	while (i < size)
	{
		pthread_join(list[i].niche, NULL);
		i++;
	}

	// create_philo(philo);
	return 0;
}


int main(int ac, char **av)
{
	t_list list;
	t_philo philo;
	(void)ac;

	printf("\tPHILO START\n");
	if (init_philo(&philo, av, &list) == FALSE)
		return (1);
	printf("\tGET FORK!!\n");
	get_fork(&list);
	printf("\tBEFORE FREE\n");
	free(philo.info);
	return 0;
}
