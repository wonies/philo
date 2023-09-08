#include "../inc/philo.h"
#define MAX_PHILOSOPHERS 1000

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
	(*philo).info->cnt = ft_atoi(av[1]);
	printf("philo cnt : %d\n", (*philo).info->cnt);
	while (i < (*philo).info->cnt)
	{
		printf("count: %d\n", i);
		new = ft_lstnew();
		// ft_lstadd_back(&list, new);
		insert_node(&list, new);
		print_list(&list);
		i++;
	}
	(*philo).info->die = ft_atoi(av[2]);
	(*philo).info->eat = ft_atoi(av[3]);
	(*philo).info->sleep = ft_atoi(av[4]);
	(*philo).info->eattime = ft_atoi(av[5]);

	return (TRUE);
}

void print_list_recursive(t_list* start_node, t_list* current_node) {
    if (current_node == start_node) {
        // 처음 노드로 돌아왔을 때 재귀 종료
        return;
    }

    // 현재 노드의 데이터 출력
    printf("Node data: %d\n", current_node->info->idx);

    // 다음 노드로 이동
    print_list_recursive(start_node, current_node->next);
}


void	*routine(void *arg)
{
	t_list *list = arg;
	
	printf("start routine\n");
	print_list_recursive(list, list);
	printf("end routine\n");
	return NULL;
}

t_bool get_fork(t_list *list)
{	
	int i = 0;
	// pthread_t threads[MAX_PHILOSOPHERS];
	
	printf("\tEnter get_fork func\n");
	int size = ft_lstsize(list);
	printf("size is : %d\n", size);
	printf("list index : %d\n", list->index);
	while (i < size)
	{
		list[i].index = i + 1;
		printf("while in index: %d\n", i);
		printf("\tindex ; %d\n", list[i].index);
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
