#include "../inc/philo.h"

t_bool  print_act(t_list *list, int nrd, int warn)
{
    ULL rec;

    if (switchoff(list))
        return (0);
    pthread_mutex_lock(&(list->share->prints));
    rec = get_time() - list->share->record;
    if (warn == 0)
    {
        printf("%llu %d %s\n", rec, nrd, ACT_FORK);
        printf("%llu %d %s\n", rec, nrd, ACT_FORK);
    }
    else if (warn == 1)
        printf("%llu %d %s\n", rec, nrd, ACT_EAT);
    else if (warn == 2)
        printf("%llu %d %s\n", rec, nrd, ACT_NAP);
    else if (warn == 3)
        printf("%llu %d %s\n", rec, nrd, ACT_THINK);
    pthread_mutex_unlock(&(list->share->prints));
    return (1);
}

void    status(t_list *list, int active)
{
    pthread_mutex_lock(&(list->active));
    list->info->status = active;
    pthread_mutex_unlock(&(list->active));
}

t_bool	option(t_list *list)
{
	pthread_mutex_lock(&(list->share->opt));
	if (list->info->option != -1)
	{
		list->info->optown++;
		if (list->info->optown == list->info->option)
		{
			list->share->opttotal++;
			if (list->share->opttotal == list->info->cnt)
			{
				pthread_mutex_lock(&(list->share->inactive));
				list->share->dead = 1;
				pthread_mutex_unlock(&(list->share->inactive));
				pthread_mutex_unlock(&(list->share->opt));
				return (1);
			}
		}
	}
	pthread_mutex_unlock(&(list->share->opt));
	return (0);
}

t_bool	switchoff(t_list *list)
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
