#include "../inc/philo.h"

void    print_status(t_list *list, int nrd, int behaivor)
{
    ULL begins;

    if (behaivor == 0)
	{
		pthread_mutex_lock(&(list->share->prints));
		begins = get_time() - list->share->record;
		printf("%llu %d has taken a fork\n", begins, nrd);
		printf("%llu %d has taken a fork\n", begins, nrd);
		pthread_mutex_unlock(&(list->share->prints));
	}
	else if (behaivor == 1)
	{
		begins = get_time() - list->share->record;
		pthread_mutex_lock(&(list->share->prints));
		printf("%llu %d is eating\n", get_time() - list->share->record, nrd);
		pthread_mutex_unlock(&(list->share->prints));
	}
}

void    moniterlife(t_list *list, ULL times)
{
    ULL cur;


    (void )list;
    cur = get_time();
    while (1)
    {
        if (get_time() - cur >= times)
            break ;
        usleep(256);
    }
}

void    mutex(t_list *list, int onoff)
{
    if (onoff == 1)
        pthread_mutex_lock(&(list->fork));
    else if (onoff == 0)
        pthread_mutex_unlock(&(list->fork));
}

void    status(t_list *list, int active)
{
    pthread_mutex_lock(&(list->active));
    list->info->status = active;
    pthread_mutex_unlock(&(list->active));
}

void    think(t_list *list, int nrd)
{
    pthread_mutex_lock(&(list->share->prints));
	printf("%llu %d is thinking\n", get_time() - list->share->record, nrd);
	pthread_mutex_unlock(&(list->share->prints));
}

t_bool  sleeps(t_list *list, int nrd)
{
    pthread_mutex_lock(&(list->share->prints));
	printf("%llu %d is sleeping\n", get_time() - list->share->record, nrd);
	pthread_mutex_unlock(&(list->share->prints));
    moniterlife(list, list->info->naptime);
    status(list, STARVE);
    return (0);
}

t_bool  eveneat(t_list *list, int nrd)
{
    list->info->taken = get_time();
    mutex(list, 1);
    print_status(list, nrd, 0);
    mutex(list->next, 1);
    print_status(list, nrd, 1);
    status(list, EAT);
    moniterlife(list, list->info->eattime);
    mutex(list, 0);
    mutex(list->next, 0);
    status(list, SLEEP);
    return (0);
}


t_bool  oddeat(t_list *list, int nrd)
{
    list->info->taken = get_time();
    mutex(list->next, 1);
    print_status(list, nrd, 0);
    mutex(list, 1);
    if (list->prev->info->status == STARVE && list->next->info->status == SLEEP)
    {
        mutex(list, 0);
        usleep(5000);
        mutex(list, 1);
    }
    print_status(list, nrd, 1);
    status(list, EAT);
    moniterlife(list, list->info->eattime);
    mutex(list->next, 0);
    mutex(list, 0);
    status(list, SLEEP);
    return (0);
}


void    eat(t_list *list, int nrd)
{
    if (nrd % 2 != 0)
        oddeat(list, nrd);
    else
        eveneat(list, nrd);
    sleeps(list, nrd);
}


void	table(t_list *list, int nrd)
{
	while (1)
	{
		eat(list, nrd);
		think(list, nrd);
	}
}

void	*routine(void *arg)
{
	t_list *list = (t_list *)arg;

	table(list, list->info->idx);
	return (NULL);
}
