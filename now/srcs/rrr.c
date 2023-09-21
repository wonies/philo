#include "../inc/philo.h"

void    onephilo(t_list *list);
t_bool	option(t_list *list);
t_bool	amidie(t_list *list);

t_bool  died(t_list *list, ULL timz)
{
    ULL lives;

    lives = list->info->lifetime;
    if (amidie(list))
		return (1);
    if (get_time() - timz >= lives)
    {
        pthread_mutex_lock(&(list->share->inactive));
        if (list->share->dead == 0)
        {
            pthread_mutex_lock(&(list->share->prints));
            printf("%llu %d is died\n", get_time() - list->info->taken, list->info->idx);
            list->share->dead = 1;
            pthread_mutex_unlock(&(list->share->prints));
        }
        pthread_mutex_unlock(&(list->share->inactive));
        return (1);
    }
    return (0);
}

void    print_status(t_list *list, int nrd, int behaivor)
{
    ULL begins;

    pthread_mutex_lock(&(list->share->prints));
    pthread_mutex_lock(&(list->share->inactive));
    if (list->share->dead == 1)
    {
        pthread_mutex_unlock(&(list->share->prints));
        pthread_mutex_unlock(&(list->share->inactive));
        return ;
    }
    pthread_mutex_unlock(&(list->share->inactive));
    if (behaivor == 0)
	{
		begins = get_time() - list->share->record;
		printf("%llu %d has taken a fork\n", begins, nrd);
		printf("%llu %d has taken a fork\n", begins, nrd);
	}
	else if (behaivor == 1)
	{
		begins = get_time() - list->share->record;
		printf("%llu %d is eating\n", get_time() - list->share->record, nrd);
	}
    pthread_mutex_unlock(&(list->share->prints));
}

t_bool    moniterlife(t_list *list, ULL times)
{
    ULL cur;
    ULL death;

    (void )list;
    cur = get_time();
    death = list->info->taken;
    if (list->info->idx == 1)
        printf("death : %d \n", list->info->lifetime);
    printf("\t\t%llu is time check :\n\n", cur - death);
    while (1)
    {
        if (died(list, death))
            return (1);
        if (get_time() - cur >= times)
            break ;
        usleep(256);
    }
    return (0);
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

t_bool    think(t_list *list, int nrd)
{
    pthread_mutex_lock(&(list->share->prints));
    pthread_mutex_lock(&(list->share->inactive));
    if (list->share->dead == 1)
    {
        pthread_mutex_unlock(&(list->share->inactive));
        pthread_mutex_unlock(&(list->share->prints));
        return (1);
    }
    pthread_mutex_unlock(&(list->share->inactive));
	printf("%llu %d is thinking\n", get_time() - list->share->record, nrd);
	pthread_mutex_unlock(&(list->share->prints));
	if (moniterlife(list, list->info->eattime - list->info->naptime))
        return (1);
    return (0);
}

t_bool    odd_think(t_list *list, int nrd)
{
    pthread_mutex_lock(&(list->share->prints));
    pthread_mutex_lock(&(list->share->inactive));
    if (list->share->dead == 1)
    {
        pthread_mutex_unlock(&(list->share->inactive));
        pthread_mutex_unlock(&(list->share->prints));
        return (1);
    }
    pthread_mutex_unlock(&(list->share->inactive));
	printf("%llu %d is thinking\n", get_time() - list->share->record, nrd);
	pthread_mutex_unlock(&(list->share->prints)); 
    if (moniterlife(list, list->info->eattime * 2 - list->info->naptime))
        return (1);
    return (0);
}


t_bool  sleeps(t_list *list, int nrd)
{
    pthread_mutex_lock(&(list->share->prints));
	if (amidie(list))
	{
		pthread_mutex_unlock(&(list->share->prints));
		return (1);
	}
	printf("%llu %d is sleeping\n", get_time() - list->share->record, nrd);
	pthread_mutex_unlock(&(list->share->prints));
    if (moniterlife(list, list->info->naptime))
        return (1);
    status(list, STARVE);
    return (0);
}

t_bool	amidie(t_list *list)
{
	pthread_mutex_lock(&(list->share->inactive));
    if (list->share->dead == 1)
    {
        pthread_mutex_unlock(&(list->share->inactive));
        return (1);
    }
    pthread_mutex_unlock(&(list->share->inactive));
	return (0);
}

t_bool  eveneat(t_list *list, int nrd)
{
    mutex(list, 1);
    if (amidie(list))
		return (1);
    print_status(list, nrd, 0);
    mutex(list->next, 1);
    if (amidie(list))
		return (1);
    print_status(list, nrd, 1);
    status(list, EAT);
    list->info->taken = get_time();
    if (moniterlife(list, list->info->eattime))
    {
        pthread_mutex_unlock(&(list->fork));
        pthread_mutex_unlock(&(list->next->fork));
        return (1);
    }
    mutex(list, 0);
    mutex(list->next, 0);
	if (option(list))
		return (1);
    if (amidie(list))
		return (1);
    status(list, SLEEP);
    return (0);
}


t_bool	yield(t_list *list)
{
	pthread_mutex_lock(&(list->prev->active));
	pthread_mutex_lock(&(list->next->active));
	if (list->prev->info->status == STARVE && 
	list->next->info->status == SLEEP)
    {
        mutex(list, 0);
        usleep(5000);
        mutex(list, 1);
		pthread_mutex_unlock(&(list->prev->active));
		pthread_mutex_unlock(&(list->next->active));
		return (1);
    }
	pthread_mutex_unlock(&(list->prev->active));
	pthread_mutex_unlock(&(list->next->active));
	return (0);
}

t_bool	option(t_list *list)
{
	//pthread_mutex_lock(&(list->share->opt));
	if (list->info->option != -1)
	{
		list->info->optown++;
		if (list->info->optown == list->info->option)
		{
			pthread_mutex_lock(&(list->share->opt));
			list->share->opttotal++;
			if (list->share->opttotal == list->info->cnt)
			{
				pthread_mutex_unlock(&(list->share->opt));
				pthread_mutex_lock(&(list->share->inactive));
				list->share->dead = 1;
				pthread_mutex_unlock(&(list->share->inactive));
				return (1);
			}
			pthread_mutex_unlock(&(list->share->opt));
		}
	}
	return (0);
}

t_bool  oddeat(t_list *list, int nrd)
{
    //t_bool circle = 0;
	
	mutex(list->next, 1);
    print_status(list, nrd, 0);
	if (amidie(list))
		return (1);
    mutex(list, 1);
	if (amidie(list))
		return (1);
	yield(list);
    print_status(list, nrd, 1);
    status(list, EAT);
    list->info->taken = get_time();
    if (moniterlife(list, list->info->eattime))
    {
        pthread_mutex_unlock(&(list->next->fork));
        pthread_mutex_unlock(&(list->fork));
        return (1);
    }
    mutex(list->next, 0);
    mutex(list, 0);
	if (option(list))
		return (1);
    if (amidie(list))
		return (1);
    status(list, SLEEP);
    return (0);
}

t_bool    eat(t_list *list, int nrd)
{
	if (nrd % 2 != 0)
    {
        if (oddeat(list, nrd))
            return (1);
    }
    else
    {
        if (eveneat(list, nrd))
            return (1);
    }
    sleeps(list, nrd);
    return (0);
}

void	table(t_list *list, int nrd)
{
    if (list->info->cnt % 2 == 0)
    {
        while (1)
        {
            if (eat(list, nrd))
                return ;
            if (think(list, nrd))
                return ;
        }
    }
    else
    {
        while (1)
        {
            if (eat(list, nrd))
                return ;
            if (odd_think(list, nrd))
                return ;
        }
    }
}

void    onetable(t_list *list)
{
    pthread_mutex_lock(&(list->share->prints));
    printf("%llu %d has taken a fork", get_time()-list->info->taken, list->info->idx);
	pthread_mutex_unlock(&(list->share->prints));
    moniterlife(list, list->info->lifetime);
}

void	*routine(void *arg)
{
	t_list *list = (t_list *)arg;

	if (list->info->cnt == 1)
	{
		onetable(list);
        return (NULL);
	}
    table(list, list->info->idx);
	return (NULL);
}
