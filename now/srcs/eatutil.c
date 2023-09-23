#include "../inc/philo.h"

static  t_status ref_stat(t_list *list)
{
    t_status    result;

    pthread_mutex_lock(&list->active);
    result = list->info->status;
    pthread_mutex_unlock(&list->active);
    return (result);
}

t_bool	yield(t_list *list)
{
	if (ref_stat(list->prev) == STARVE && ref_stat(list->next) == SLEEP)
    {
        mutex(list, 0);
        usleep(1000);
        mutex(list, 1);
		return (1);
    }
	return (0);
}
