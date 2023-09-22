#include "../inc/philo.h"

unsigned long long get_time(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) < 0)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

t_bool    moniterlife(t_list *list, ULL times)
{
    ULL cur;
    ULL lasteat;

    (void )list;
    cur = get_time();
    lasteat = list->info->taken;
    while (1)
    {
		if (died(list, lasteat))
            return (1);
        if (get_time() - cur >= times)
            break ;
        usleep(256);
    }
    return (0);
}
