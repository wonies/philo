#include "../inc/philo.h"

unsigned long long get_time(void);

void print_list_recursive(t_list* start_node, t_list* current_node) {

    if (current_node == NULL) {
        return; // 현재 노드가 NULL이면 종료
    }
	printf("recursive data: %d\n", current_node->info->idx);
    print_list_recursive(start_node, current_node->next);
    if (current_node == start_node) {
        return;
    }
}

//모니터링
//공유자원??

// void	*routine(void *arg)
// {
// 	t_list *list = * (t_list **)arg;
	
// 	double	difftime;

// 	difftime = list->info->die - list->info->eat;
// 	printf("diff time : {%f}\n", difftime);
// 	int i = 0;
// 	int idxx = list->info->idx;
// 	int times = 0;
// 	printf("\t list's idxx {%d}\n", idxx);
// 	while (1)
// 	{
// 	if (list->info->idx % 2 != 0)
// 	{
// 		// printf("\tlist  ODD index [[[%d]]]\n", list->info->idx);
// 		if (list->next->use == 0 && list->use == 0)
// 		{
// 			usleep(1000);
// 			pthread_mutex_lock(&(list->fork));
// 			pthread_mutex_lock(&(list->info->prints));
// 			list->use = 1;
// 			list->next->use = 1;
// 			printf("\t %d %d philosopher has taken a fork\n", times,  list->info->idx);
// 			printf("\t %d %d philosopher has taken a fork\n", times,  list->info->idx);
// 			printf("\t %d %d philosopher is eating\n", times, list->info->idx);
// 			pthread_mutex_unlock(&(list->info->prints));
// 			pthread_mutex_unlock(&(list->fork));
// 			list->use = 0;
// 			list->next->use = 0;
// 		}
// 		else if ((list->next->use != 0 && list->use != 0) || (list->next->use != 0 && list->use == 0) || (list->next->use == 0 && list->use != 0))
// 		{
// 			if (list->status == 0)
// 			{
// 				//thinking = 자는 시간  - 먹는 시간
// 				usleep(1000);
// 				pthread_mutex_lock(&(list->info->sleeping));
// 				pthread_mutex_lock(&(list->info->prints));
// 				printf("\t\033[0;31m %d %d philosopher is sleeping\n\033[0m", times, list->info->idx);
// 				pthread_mutex_unlock(&(list->info->prints));
// 				pthread_mutex_unlock(&(list->info->sleeping));
// 				list->status = 1;
// 				list->use = 0;
// 			}
// 			else
// 			{
// 				usleep(10000);
// 				pthread_mutex_lock(&(list->info->thinking));
// 				pthread_mutex_lock(&(list->info->prints));
// 				printf("\t\033[0;32m %d %d philosopher is thinking\n\033[0m", times, list->info->idx);
// 				pthread_mutex_unlock(&(list->info->prints));
// 				pthread_mutex_unlock(&(list->info->thinking));
// 				list->status = 0;
// 				list->use = 0;
// 			}
// 		}	
// 	}
// 	else if (list->info->idx % 2 == 0)
// 	{
// 		// printf("\tlist  EVEN index [[[%d]]]\n", list->info->idx);
// 		if (list->next->use == 0 && list->use == 0)
// 		{
// 			usleep(1000*1000);
// 			pthread_mutex_lock(&(list->fork));
// 			pthread_mutex_lock(&(list->info->prints));
// 			list->use = 1;
// 			printf("\t\033[0;31m %d %d philosopher is sleeping\n\033[0m", times, list->info->idx);
// 			pthread_mutex_unlock(&(list->info->prints));
// 			pthread_mutex_unlock(&(list->fork));
// 			list->status = 0;
// 			list->use = 0;
// 		}
// 		else if ((list->next->use != 0 && list->use != 0) || (list->next->use != 0 && list->use == 0) || (list->next->use == 0 && list->use != 0))
// 		{
// 			if (list->status == 0)
// 			{
// 				usleep(1000*1000);
// 				pthread_mutex_lock(&(list->info->sleeping));
// 				pthread_mutex_lock(&(list->info->prints));
// 				printf("\t\033[0;31m %d %d philosopher is sleeping\n\033[0m", times, list->info->idx);
// 				pthread_mutex_unlock(&(list->info->prints));
// 				pthread_mutex_unlock(&(list->info->sleeping));
// 				list->use = 0;
// 				list->status = 1;
// 			}
// 			else
// 			{
// 				usleep(1000*1000);
// 				pthread_mutex_lock(&(list->info->thinking));
// 				pthread_mutex_lock(&(list->info->prints));
// 				printf("\t\033[0;32m %d %d philosopher is thinking\n\033[0m", times, list->info->idx);
// 				pthread_mutex_unlock(&(list->info->prints));
// 				pthread_mutex_unlock(&(list->info->thinking));
// 				list->use = 0;
// 				list->status = 0;
// 			}
// 		}
// 	}
// 	times += list->info->eat;
// 	i++;
// 	if (i == 10)
// 		break ;
// 	}
// 	// if (list->info->idx %)

// 	return NULL;
// }	


// t_bool	get_fork(t_list **list)
// {
// 	int	size;
// 	t_list *cur = *list;

// 	size = ft_lstsize(list);
// 	printf("\tlist size : {%d}\n", size);
// 	// pthread_mutex_init(*philo.prints, NULL);
// 	while (1)
// 	{
// 		pthread_mutex_init(&cur->fork, NULL);
// 		pthread_mutex_init(&cur->info->prints, NULL);
// 		pthread_mutex_init(&cur->info->sleeping, NULL);
// 		pthread_mutex_init(&cur->info->thinking, NULL);
// 		cur = cur->next;
// 		if (*list == cur)
// 			break ;
// 	}
// 	t_list *cur1 = *list;
// 	while (1)
// 	{
// 		printf("\tidx check in get-fork %d\n", cur1->info->idx);
//         if (pthread_create(&cur1->niche, NULL, routine, &cur1) != 0)
// 			printf("-----seg-------\n");
// 		cur1 = cur1->next;
// 		if (*list == cur1)
// 			break ;
// 	}
// 	t_list *cur2 = *list;
// 	while (1)
// 	{
// 		pthread_join(cur2->niche, NULL);
// 		cur2 =cur2->next;
// 		if (*list == cur2)
// 			break ;
// 	}
// 	return 0;
// }

// t_bool	get_fork(t_list **list)
// {
// 	int	i;
// 	int	size;

// 	i = 0;
// 	size = ft_lstsize(list);
// 	printf("\tlist size : {%d}\n", size);
// 	// pthread_mutex_init(*philo.prints, NULL);
// 	while (i < size)
// 	{
// 		pthread_mutex_init(&(*list)[i].fork, NULL);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < size)
// 	{
// 		// list[i]->info->idx = i + 1;
// 		printf("idx check %d\n", list[i]->info->idx);
//         if (pthread_create(&(list)[i]->niche, NULL, &routine, &list[i]) != 0)
// 			printf("-----seg-------\n");

//         // pthread_detach((*list)[i].niche);
// 		// // pthread_mutex_init(&list[i]->fork, NULL);
// 		// pthread_create(&list[i]->niche, NULL, &routine, list[i]);
// 		// pthread_detach(list[i]->niche);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < size)
// 	{
// 		pthread_join(list[i]->niche, NULL);
// 		i++;
// 	}
// 	return 0;
// }

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
	pthread_mutex_destroy(&(list->share->circle));
	while (++i < list->info->cnt)
	{
		pthread_mutex_destroy(&(list->fork));
		pthread_mutex_destroy(&(list->active));
		list = list->next;
	}
	// free(*list.info);
	return (0);
}
