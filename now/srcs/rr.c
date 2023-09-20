#include "../inc/philo.h"

void    onephilo(t_list *list);

t_bool  died(t_list *list, ULL timz)
{
    ULL lives;

    lives = list->info->lifetime;
    pthread_mutex_lock(&(list->share->inactive));
    if (list->share->dead == 1)
    {
        pthread_mutex_unlock(&(list->share->inactive));
        return (1);
    }
    pthread_mutex_unlock(&(list->share->inactive));
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
        pthread_mutex_lock(&(list->share->inactive));
        pthread_mutex_unlock(&(list->share->inactive));
        return (1);
    }
    return (0);
}

// t_bool  died(t_list *list, ULL timz)
// {
//     ULL lives;

//     lives = list->info->lifetime;
//     // if (list->info->idx == 5)
//     // {
//     //    timz +=  list->info->eattime * 1000;
//     //     printf("\t\ttimz: %llu\n\n", get_time() - timz);
//     // }
//     ULL cur = get_time();
//     if (list->share->dead == 1)
//         return 1;
//     // printf("current time - last eaten : %llu\n", get_time() - timz);
//     if (list->info->cnt == 1 && get_time() - timz >= lives)
//     {
//         if (lives <= (ULL)list->info->eattime)
//         {
//             pthread_mutex_lock(&(list->share->prints));
//             printf("\t\tdied time : %llu \torder : %d\n", lives, list->info->idx);
//             printf("%llu %d is died\n", lives, list->info->idx);
//             pthread_mutex_unlock(&(list->share->prints));
//             pthread_mutex_lock(&(list->share->inactive));
//             list->share->dead = 1;
//             pthread_mutex_unlock(&(list->share->inactive));
//             return (1);
//         }
//         else
//         {
//             pthread_mutex_lock(&(list->share->prints));
//             printf("\t\tdied time : %llu \torder : %d\n", lives, list->info->idx);
//             printf("%llu %d is died\n", cur - list->info->taken, list->info->idx);
//             pthread_mutex_unlock(&(list->share->prints));
//             pthread_mutex_lock(&(list->share->inactive));
//             list->share->dead = 1;
//             pthread_mutex_unlock(&(list->share->inactive));
//             return 1;
//         }
//     }
//     else if (get_time() - timz >= lives)
//     {
//         pthread_mutex_lock(&(list->share->inactive));
//         if (list->share->dead == 0)
//         {
//             pthread_mutex_lock(&(list->share->prints));
//             printf("\t\tdied time : %llu \torder : %d\n", lives, list->info->idx);
//             printf("%llu %d is died\n", cur - list->info->taken, list->info->idx);
//             pthread_mutex_unlock(&(list->share->prints));
//         }
//         pthread_mutex_unlock(&(list->share->inactive));
//         pthread_mutex_lock(&(list->share->inactive));
//         list->share->dead = 1;
//         pthread_mutex_unlock(&(list->share->inactive));
//         return (1);
//     }
//     return (0);
// }

// void    dead(t_list *list)
// {
//     pthread_mutex_lock(&(list->share->inactive));
// 	list->share->dead = 1;
//     pthread_mutex_unlock(&(list->share->inactive));
//     // pthread_mutex_destroy(&(list->share->prints));
// 	// pthread_mutex_destroy(&(list->share->inactive));
// }

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
    //printf("--- dead flag ---: {%d} | {%d} \n", list->share->dead, list->info->idx);
    printf("\t\t%llu is time check :\n\n", cur - death);
    while (1)
    {
        if (died(list, death))
        {
            // printf("\t\tdeath time : %llu\n\n", get_time() - death);
            // // dead(list);
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
    if (list->info->cnt % 2 != 0)
    {
        if (moniterlife(list, list->info->eattime * 2 - list->info->naptime))
            return 1;
    }
    else if (moniterlife(list, list->info->eattime - list->info->naptime))
        return 1;
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
    // printf ("left_time: %llu\n", get_time() - list->info->eattime - list->info->naptime);
	pthread_mutex_unlock(&(list->share->prints)); 
    if (moniterlife(list, list->info->eattime * 2 - list->info->naptime))
        return 1;
    return (0);
}


t_bool  sleeps(t_list *list, int nrd)
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
    pthread_mutex_lock(&(list->share->inactive));
    if (list->share->dead == 1)
    {
        pthread_mutex_unlock(&(list->share->inactive));
        return (1);
    }
    pthread_mutex_unlock(&(list->share->inactive));
    printf("\t\tlast taken : %llu %d\n", get_time() -list->info->taken, list->info->idx);
    mutex(list, 1);
    pthread_mutex_lock(&(list->share->inactive));
    if (list->share->dead == 1)
    {
        pthread_mutex_unlock(&(list->share->inactive));
        return (1);
    }
    pthread_mutex_unlock(&(list->share->inactive));
    print_status(list, nrd, 0);
    mutex(list->next, 1);
    pthread_mutex_lock(&(list->share->inactive));
    if (list->share->dead == 1)
    {
        pthread_mutex_unlock(&(list->share->inactive));
        return (1);
    }
    pthread_mutex_unlock(&(list->share->inactive));
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
    printf("list->info->option : {%d}\n", list->info->option);
    if (list->info->option != -1)
    {
        list->info->optown++;
        printf("\t\topt own : %d\n", list->info->optown);
        if (list->info->optown == list->info->option)
        {
            list->share->opttotal++;
            printf("list->share->optional : {%d}\n", list->share->opttotal);
            pthread_mutex_lock(&(list->share->opt));
            if (list->share->opttotal == list->info->option)
            {
                pthread_mutex_lock(&(list->share->inactive));
                list->share->dead = 1;
                pthread_mutex_unlock(&(list->share->opt));
                pthread_mutex_unlock(&(list->share->inactive));
                return (1);
            }
            pthread_mutex_unlock(&(list->share->opt));
        }
    }
    // list->info->lifetime -= 200;
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
    mutex(list->next, 1);
    print_status(list, nrd, 0);
    pthread_mutex_lock(&(list->share->inactive));
    if (list->share->dead == 1)
    {
        pthread_mutex_unlock(&(list->share->inactive));
        return (1);
    }
    pthread_mutex_unlock(&(list->share->inactive));
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
    if (list->info->option != -1)
        {
            list->info->optown++;
            printf("\t\topt own : %d\n", list->info->optown);
            if (list->info->optown == list->info->option)
            {
                list->share->opttotal++;
                printf("list->share->optional : {%d}\n", list->share->opttotal);
                pthread_mutex_lock(&(list->share->opt));
                if (list->share->opttotal == list->info->option)
                {
                    
                    // pthread_mutex_lock(&(list->share->inactive));
                    // list->share->dead = 1;
                    // pthread_mutex_unlock(&(list->share->opt));
                    pthread_mutex_unlock(&(list->share->inactive));
                    return (1);
                }
                pthread_mutex_unlock(&(list->share->opt));
            }
        }
    // list->info->lifetime -= 200;
    mutex(list->next, 0);
    mutex(list, 0);
    pthread_mutex_lock(&(list->share->inactive));
    if (list->share->dead == 1)
    {
        pthread_mutex_unlock(&(list->share->inactive));
        return (1);
    }
    pthread_mutex_unlock(&(list->share->inactive));
    status(list, SLEEP);
    return (0);
}

t_bool    eat(t_list *list, int nrd)
{
    // list->info->lifetime = 410;
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

void    onephilo(t_list *list)
{
    ULL cur;
    ULL printtimes;
    
    // list->info->taken = get_time();
    cur = get_time();
    printf("cur time : %llu\n", cur);
    printf("basic time : %llu\n", list->info->taken);
    printtimes = cur - list->info->taken;
    printf("printtime : %llu\n", printtimes);
    pthread_mutex_lock(&(list->share->prints));
    printf("%llu %d has taken a fork", get_time()-list->info->taken, list->info->idx);
    // printf("%llu %d has taken a fork", printtimes, list->info->idx);
    pthread_mutex_unlock(&(list->share->prints));
    // died(list, list->info->lifetime);
    // died(list, list->info->lifetime);
    moniterlife(list, list->info->lifetime);
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
