#include "../inc/philo.h"

t_bool  died(t_list *list, ULL timz)
{
    ULL lives;

    lives = list->info->lifetime;
    // if (list->info->idx == 5)
    // {
    //    timz +=  list->info->eattime * 1000;
    //     printf("\t\ttimz: %llu\n\n", get_time() - timz);
    // }
    if (get_time() - timz >= lives)
    {
        printf("\t\tdied time : %llu \torder : %d\n", get_time() - timz, list->info->idx);
        pthread_mutex_lock(&(list->share->prints));
        printf("%llu %d is died\n", get_time() - list->info->taken, list->info->idx);
        pthread_mutex_unlock(&(list->share->prints));
        pthread_mutex_lock(&(list->share->inactive));
        list->share->dead = 1;
        pthread_mutex_unlock(&(list->share->inactive));
        return (1);
    }
    return (0);
}

void    dead(t_list *list)
{
    pthread_mutex_lock(&(list->share->inactive));
	list->share->dead = 1;
    pthread_mutex_unlock(&(list->share->inactive));
    // pthread_mutex_destroy(&(list->share->prints));
	// pthread_mutex_destroy(&(list->share->inactive));
}

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

t_bool    moniterlife(t_list *list, ULL times)
{
    ULL cur;
    ULL death;

    (void )list;
    cur = get_time();
    death = list->info->taken;
    printf("\t\t%llu is time check :\n\n", cur - death);
    while (1)
    {
        if (died(list, death))
        {
            printf("\t\tdeath time : %llu\n\n", get_time() - death);
            // dead(list);
            return (1);
        }
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
	printf("%llu %d is thinking\n", get_time() - list->share->record, nrd);
	pthread_mutex_unlock(&(list->share->prints));
    return (0);
}

t_bool  sleeps(t_list *list, int nrd)
{
    pthread_mutex_lock(&(list->share->prints));
	printf("%llu %d is sleeping\n", get_time() - list->share->record, nrd);
	pthread_mutex_unlock(&(list->share->prints));
    if (moniterlife(list, list->info->naptime))
    {
        printf("\t\t----ORDER---%d\n", list->info->idx);
        return (1);
    }
    status(list, STARVE);
    return (0);
}

t_bool  eveneat(t_list *list, int nrd)
{
     printf("\t\tlast taken : %llu %d\n", get_time() -  list->info->taken, list->info->idx);
     if (died(list, list->info->taken))
    {
        printf("\t\t----ORDER---%d\n", list->info->idx);
        pthread_mutex_unlock(&(list->fork));
        // dead(list);
        return 1;
    }
    printf("\t\tlast taken : %llu %d\n", get_time() -list->info->taken, list->info->idx);
    mutex(list, 1);
    if (died(list, list->info->taken))
    {
        printf("\t\t----ORDER---%d\n", list->info->idx);
        pthread_mutex_unlock(&(list->fork));
        // dead(list);
        return 1;
    }
    print_status(list, nrd, 0);
    mutex(list->next, 1);
    print_status(list, nrd, 1);
    status(list, EAT);
    list->info->taken = get_time();
    if (moniterlife(list, list->info->eattime))
    {
        printf("\t\t----ORDER---%d\n", list->info->idx);
        pthread_mutex_unlock(&(list->fork));
        pthread_mutex_unlock(&(list->next->fork));
        return (1);
    }
    mutex(list, 0);
    mutex(list->next, 0);
    if (died(list, list->info->taken))
    {
        // pthread_mutex_unlock(&(list->next->fork));
        printf("\t\t----ORDER---%d\n", list->info->idx);
        // dead(list);
        return 1;
    }
    status(list, SLEEP);
    return (0);
}


t_bool  oddeat(t_list *list, int nrd)
{
    // if (list->info->idx == list->info->cnt)
    //     list->info->taken -= list->info->eattime * 1000;
    printf("\t\tlast taken : %llu %d\n", get_time() -  list->info->taken, list->info->idx);
    if (died(list, list->info->taken))
    {
        printf("\t\t----ORDER---%d\n", list->info->idx);
        pthread_mutex_unlock(&(list->next->fork));
        // dead(list);
        return 1;
    }
    mutex(list->next, 1);
    print_status(list, nrd, 0);
    if (died(list, list->info->taken))
    {
        printf("\t\t----ORDER---%d\n", list->info->idx);
        pthread_mutex_unlock(&(list->fork));
        // dead(list);
        return 1;
    }
    mutex(list, 1);
    if (list->prev->info->status == STARVE && list->next->info->status == SLEEP)
    {
        mutex(list, 0);
        usleep(5000);
        mutex(list, 1);
    }
    print_status(list, nrd, 1);
    status(list, EAT);
    list->info->taken = get_time();
    if (moniterlife(list, list->info->eattime))
    {
        printf("\t\t----ORDER---%d\n", list->info->idx);
        pthread_mutex_unlock(&(list->next->fork));
        pthread_mutex_unlock(&(list->fork));
        return (1);
    }
    mutex(list->next, 0);
    mutex(list, 0);
    if (died(list, list->info->taken))
    {
        // pthread_mutex_unlock(&(list->next->fork));
        printf("\t\t----ORDER---%d\n", list->info->idx);
        // dead(list);
        return 1;
    }
    status(list, SLEEP);
    return (0);
}


t_bool    eat(t_list *list, int nrd)
{
    if (nrd % 2 != 0)
    {
        if (died(list, list->info->taken))
        {
            printf("\t\t----ORDER---%d\n", list->info->idx);
            pthread_mutex_unlock(&(list->fork));
            // dead(list);
            return 1;
        }
        if (oddeat(list, nrd))
            return (1);
    }
    else
    {
        if (died(list, list->info->taken))
        {
            printf("\t\t----ORDER---%d\n", list->info->idx);
            pthread_mutex_unlock(&(list->fork));
            // dead(list);
            return 1;
        }
        if (eveneat(list, nrd))
            return (1);
    }
    sleeps(list, nrd);
    return (0);
}

void	table(t_list *list, int nrd)
{
	while (1)
	{
		if (eat(list, nrd))
            break ;
		if (think(list, nrd))
            break ;
	}
}

void    onephilo(t_list *list)
{
    ULL cur;
    ULL printtimes;
    
    cur = get_time();
    printtimes = cur - list->info->taken; 
    pthread_mutex_lock(&(list->share->prints));
    printf("%llu %d has taken a fork", printtimes, list->info->idx);
    pthread_mutex_unlock(&(list->share->prints));
    died(list, list->info->lifetime);
}

void	*routine(void *arg)
{
	t_list *list = (t_list *)arg;

	if (list->info->cnt == 1)
	{
		onephilo(list);
        return (NULL);
	}
    table(list, list->info->idx);
	return (NULL);
}
