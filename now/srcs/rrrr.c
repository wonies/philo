#include "../inc/philo.h"

t_bool    think(t_list *list, int nrd)
{
    if (switchoff(list))
        return (1);
    print_act(list, nrd, 3);
    if (list->info->cnt % 2 == 0)
    {
        if (moniterlife(list, (list->info->eattime - list->info->naptime)
            * (list->info->eattime >= list->info->naptime)))
            return (1);
    }
    else
    {
        if (moniterlife(list, ((list->info->eattime * 2 - list->info->naptime))
		* (list->info->eattime >= list->info->naptime)))
            return (1);
    }
	return (0);
}

