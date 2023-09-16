#include "../inc/philo.h"
void	mutex(t_list *list, int onoff);
void	*routine(void *arg);
void	sleeps(t_list *list, int nrd);
void	moniterlife(unsigned long long times);
void	think(t_list *list, int nrd);

t_bool	even_odd(int n)
{
	if (n % 2 != 0)
		return (FALSE);
	else
		return (TRUE);
	return (TRUE);
}

void	print_status(t_list *list, int nrd, int behaivor)
{
	if (behaivor == 0)
	{
		pthread_mutex_lock(&(list->share->prints));
		printf("%llu %d has taken a fork\n", get_time() - list->share->record, nrd);
		printf("%llu %d has taken a fork\n", get_time() - list->share->record, nrd);
		pthread_mutex_unlock(&(list->share->prints));
	}
	else if (behaivor == 1)
	{
		pthread_mutex_lock(&(list->share->prints));
		printf("%llu %d is eating\n", get_time() - list->share->record, nrd);
		pthread_mutex_unlock(&(list->share->prints));
	}
}

void	eat(t_list *list, int nrd)
{
	mutex(list, 1);
	print_status(list, nrd, 0);
	mutex(list->next, 1);
	print_status(list, nrd, 1);
	//usleep(list->info->eattime * 1000);
	moniterlife(list->info->eattime);
	mutex(list->next, 0);
	mutex(list, 0);
	sleeps(list, nrd);
}

// void	eating(t_list *list, int nrd)
// {
// 	pthread_mutex_lock(&(list->fork));
// 	pthread_mutex_lock(&(list->share->prints));
// 	printf("%llu %d has taken a fork\n", get_time() - list->share->record, nrd);
// 	pthread_mutex_unlock(&(list->share->prints));
// 	pthread_mutex_lock(&(list->share->prints));
// 	printf("%llu %d has taken a fork\n", get_time() - list->share->record, nrd);
// 	pthread_mutex_unlock(&(list->share->prints));
// 	pthread_mutex_lock(&(list->next->fork));
// 	pthread_mutex_unlock(&(list->next->fork));
// 	usleep(list->info->eattime * 1000);
// 	moniterlife(list->info->eattime);
// 	pthread_mutex_unlock(&(list->fork));
// 	pthread_mutex_lock(&(list->share->prints));
// 	printf("%llu %d is eating\n", get_time() - list->share->record, nrd);
// 	pthread_mutex_unlock(&(list->share->prints));
// }

void	sleeps(t_list *list, int nrd)
{
	pthread_mutex_lock(&(list->share->prints));
	printf("%llu %d is sleeping\n", get_time() - list->share->record, nrd);
	pthread_mutex_unlock(&(list->share->prints));
	// usleep(list->info->naptime * 1000);
	moniterlife(list->info->naptime);
	//think(list, nrd);
}

void	think(t_list *list, int nrd)
{
	unsigned long long thinktime;

	thinktime = list->info->lifetime - (list->info->eattime + list->info->naptime);
	pthread_mutex_lock(&(list->share->prints));
	printf("%llu %d is thinking\n", get_time() - list->share->record, nrd);
	pthread_mutex_unlock(&(list->share->prints));
	moniterlife(thinktime);
	//usleep((list->info->lifetime - (list->info->eattime + list->info->naptime)) * 1000);
	// moniterlife((list->info->eattime - list->info->naptime));
}

void	eventable(t_list *list, int nrd)
{
	// int	n;
	// t_list *cur;
	// // int	limits = 0;
	// int i = 0;
	if (nrd % 2 == 0)
		usleep(list->info->eattime * 1000); //시간쪼개기 ?
	while (1)
	{
		eat(list, nrd);
		think(list, nrd);
		// sleeps(list, nrd);
		// think(list, nrd);
		// i++;
		// if (i == 10)
		// 	break ;
	}
	// if (nrd % 2 != 0)
	// {
	// 	eat(list, nrd);
	// 	sleeps(list, nrd); //eat - sleep
	// 	think(list, nrd); //think  내가 죽었는 지 확인 lifetime - 기다리는 시간 < 0 ->die!
	// }
	// else
	// {
	// 	usleep(list->info->eattime);
	// 	eat(list, nrd);
	// 	sleeps(list, nrd);
	// 	think(list, nrd);
	// }
}

void	*routine(void *arg)
{
	t_list *list = * (t_list **)arg;
	t_bool	g_eord;

	g_eord = even_odd(list->info->cnt);
	// printf("\tindex : {%d}\n", list->info->idx);
	if (g_eord)
	{
		// printf("\n---check---\n");
		eventable(list, list->info->idx);
	}
	// else
	// 	oddtable(&list);
	return (NULL);
}

void	mutex(t_list *list, int onoff)
{
	if (onoff == 1 && list->info->lock == 0)
	{
		pthread_mutex_lock(&(list->fork));     
		//pthread_mutex_lock(&(list->share->prints));
		list->info->lock = 1;
		// list->info->moniter = 1;
	}
	else if (onoff == 0 && list->info->lock == 1)
	{
		// pthread_mutex_unlock(&(list->share->prints));
		pthread_mutex_unlock(&(list->fork));
		list->info->lock = 0;
		// list->info->moniter = 0;
	}
}

void	moniterlife(unsigned long long times)
{
	unsigned long long cur;

	cur = get_time();
	while (1)
	{
		if (get_time() - cur >= times)
			break ;
		usleep(1000);
	}
}