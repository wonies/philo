#include "../inc/philo.h"

void	mutex(t_list *list, int onoff);
void	*routine(void *arg);
t_bool	sleeps(t_list *list, int nrd);
// void	moniterlife(t_list *list, unsigned long long times);
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
	unsigned long long begins;

	if (behaivor == 0)
	{
		pthread_mutex_lock(&(list->share->prints));
		begins = get_time() - list->share->record;
		// printf("%llu %d has taken a fork\n", get_time() - list->share->record, nrd);
		// printf("%llu %d has taken a fork\n", get_time() - list->share->record, nrd);
		printf("%llu %d has taken a fork\n", begins, nrd);
		printf("%llu %d has taken a fork\n", begins, nrd);
		pthread_mutex_unlock(&(list->share->prints));
	}
	else if (behaivor == 1)
	{
		begins = get_time() - list->share->record;
		pthread_mutex_lock(&(list->share->prints));
		//died(list, begins);
		printf("%llu %d is eating\n", get_time() - list->share->record, nrd);
		pthread_mutex_unlock(&(list->share->prints));
	}
}

t_bool	eat(t_list *list, int nrd)
{
	printf("\t\tphilo %d is %d\n", nrd, list->info->status);
	if (nrd % 2 != 0)
	{
		list->info->taken = get_time();
		printf("\t\t%llu is last taken time \n", list->info->taken);
		mutex(list->next, 1);
		print_status(list, nrd, 0);
		mutex(list, 1);
		// printf("prev list {%d}\n", list->prev->info->idx);
		if (list->prev->info->status == STARVE && list->next->info->status == SLEEP)
		{
			// && list->next->info->status == SLEEP
			printf("\t %d's status && %d status\n", nrd, list->next->info->status);
			printf("\t\tphilo %d is putting down\n", nrd);
			mutex(list, 0);
			usleep(5000);
			mutex(list, 1);
		}
		print_status(list, nrd, 1);
		pthread_mutex_lock(&(list->active));
		list->info->status = EAT;
		pthread_mutex_unlock(&(list->active));
		//moniterlife(list, list->info->eattime);
		if (moniterlife(list, list->info->eattime))
		{
			pthread_mutex_unlock(&(list->next->fork));
			pthread_mutex_unlock(&(list->fork));
			return 1;
		}
		mutex(list->next, 0);
		mutex(list, 0);
		pthread_mutex_lock(&(list->active));
		list->info->status = SLEEP;
		pthread_mutex_unlock(&(list->active));
		return 0;
	}
	else 
	{
		mutex(list, 1);
		print_status(list, nrd, 0);
		mutex(list->next, 1);
		// if (list->prev->info->status == STARVE && list->next->info->status == STARVE)
		// {
		// 	mutex(list, 0);
		// 	usleep(5000);
		// 	mutex(list, 1);
		// }
		// if (list->prev->info->status == STARVE && list->next->info->status == EAT)
		// {
		// 	// && list->next->info->status == SLEEP
		// 	printf("\t\tphilo %d is putting down\n", nrd);
		// 	mutex(list, 0);
		// 	usleep(5000);
		// 	mutex(list, 1);
		// 	print_status(list, nrd, 1);
		// 	moniterlife(list->info->eattime);
		// 	mutex(list->next, 0);
		// 	mutex(list, 0);
		// 	return ;
		// }
		print_status(list, nrd, 1);
		pthread_mutex_lock(&(list->active));
		list->info->status = EAT;
		pthread_mutex_unlock(&(list->active));
		if (moniterlife(list, list->info->eattime))
		{
			pthread_mutex_unlock(&(list->fork));
			pthread_mutex_unlock(&(list->next->fork));
			return 1;
		}
		mutex(list, 0);
		mutex(list->next, 0);
		pthread_mutex_lock(&(list->active));
		list->info->status = SLEEP;
		pthread_mutex_unlock(&(list->active));
		return 0;
	}
	// mutex(list, 1);
	// print_status(list, nrd, 0);
	// mutex(list->next, 1);
	// print_status(list, nrd, 1);
	// //usleep(list->info->eattime * 1000);
	// moniterlife(list->info->eattime);
	// mutex(list->next, 0);
	// mutex(list, 0);
	
	if (sleeps(list, nrd))
		return 1;
}

t_bool	sleeps(t_list *list, int nrd)
{
	printf("\t\tphilo %d is %d\n", nrd, list->info->status);
	// pthread_mutex_lock(&(list->active));
	// list->info->status = SLEEP;
	// pthread_mutex_unlock(&(list->active));
	pthread_mutex_lock(&(list->share->prints));
	printf("%llu %d is sleeping\n", get_time() - list->share->record, nrd);
	pthread_mutex_unlock(&(list->share->prints));
	// usleep(list->info->naptime * 1000);
	if (moniterlife(list, list->info->naptime))
		return 1;
	pthread_mutex_lock(&(list->active));
	list->info->status = STARVE;
	pthread_mutex_unlock(&(list->active));
	//think(list, nrd);
	return 0;
}

void	think(t_list *list, int nrd)
{
	// unsigned long long thinktime;

	// thinktime = list->info->lifetime - (list->info->eattime + list->info->naptime);
	printf("\t\tphilo %d is %d\n", nrd, list->info->status);
	// pthread_mutex_lock(&(list->active));
	// list->info->status = STARVE;
	// pthread_mutex_unlock(&(list->active));
	pthread_mutex_lock(&(list->share->prints));
	printf("%llu %d is thinking\n", get_time() - list->share->record, nrd);
	pthread_mutex_unlock(&(list->share->prints));
	// printf("\t\tphilo %d is %d\n", nrd, list->info->status);
	//moniterlife(thinktime);

	//usleep((list->info->lifetime - (list->info->eattime + list->info->naptime)) * 1000);
	// moniterlife((list->info->eattime - list->info->naptime));
}

void	eventable(t_list *list, int nrd)
{
	// int	n;
	// t_list *cur;
	// // int	limits = 0;
	// int i = 0;
	if (list->info->cnt % 2 !=0)
	{
		// if (list->info->idx == list->info->cnt)
		// 	usleep(list->info->eattime * 1000);
		// if (nrd % 2 == 0)
		// {
		// 	// printf("\t\tphilo %d wait s\n", nrd);
		// 	usleep(list->info->eattime * 1000);	
		// 	// printf("\t\tphilo %d wait e\n", nrd);
		// }
	while (1)
	{
		if (eat(list, nrd))
			break; 
		think(list, nrd);
		// sleeps(list, nrd);
		// think(list, nrd);
		// i++;
		// if (i == 10)
		// 	break ;
	}
	}
	else
	{
	// if (nrd % 2 == 0)
	// 	usleep(list->info->eattime * 1000); //시간쪼개기 ?
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
	t_list *list = (t_list *)arg;
	// t_bool	g_eord;

	// g_eord = even_odd(list->info->cnt);
	// printf("\tindex : {%d}\n", list->info->idx);
	// if (g_eord)
	// printf("lock : %d %d\n", list->info->idx, list->info->lock);
	eventable(list, list->info->idx);
	
	// if (g_eord)
	// {
	// 	// printf("\n---check---\n");
	// 	eventable(list, list->info->idx);
	// }
	// else
	// 	oddtable(&list);
	return (NULL);
}

void	mutex(t_list *list, int onoff)
{
	//if (onoff == 1 && list->info->lock == 0)
	if (onoff == 1)
	{
		pthread_mutex_lock(&(list->fork));
		//pthread_mutex_lock(&(list->share->prints));
		// list->info->moniter = 1;
	}
	//else if (onoff == 0 && list->info->lock == 1)
	else if (onoff == 0)
	{
		// pthread_mutex_unlock(&(list->share->prints));
		
		pthread_mutex_unlock(&(list->fork));
		
		// list->info->moniter = 0;
	}
}

t_bool	moniterlife(t_list *list, unsigned long long times)
{
	unsigned long long cur;
	unsigned long long death;

	(void )list;
	cur = get_time();
	death = list->info->taken;
	while (1)
	{
		if (died(list, death))
		{
			dead(list);
			return (1);
		}
		if (get_time() - cur >= times)
			break ;
		usleep(256);
	}
	return (0);
}

t_bool	died(t_list *list, unsigned long long timz)
{
	// unsigned long long deadtime;
	unsigned long long lives;

	// pthread_mutex_lock(&(list->share->prints));
	// 	
	// pthread_mutex_unlock(&(list->share->prints));
//	deadtime = get_time();
	lives = list->info->lifetime;
	if (get_time() - timz >= lives)
	{
		pthread_mutex_lock(&(list->share->prints));
			printf("\t\t if its in ->>1234 \t\t\n");
		printf("%d is died\n", list->info->idx);
		pthread_mutex_unlock(&(list->share->prints));
		return (1);
	}
	return (0);
}

t_bool	dead(t_list *list)
{
	// if (list->info->status == EAT)
	// {
	// 	pthread_mutex_unlock(&(list->fork));
	// 	pthread_mutex_unlock(&(list->next->fork));
	// }
	pthread_mutex_lock(&(list->active));
	list->info->status = DEATH;
	pthread_mutex_unlock(&(list->active));
	return 1;
}
