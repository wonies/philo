#include "../inc/philo.h"

static void		init_share(t_philo *share)
{
	pthread_mutex_init((&share->prints), NULL);
	pthread_mutex_init((&share->inactive), NULL);
	share->start = 0;
	share->times = 0;
	share->dead = 0;
	share->record = get_time();
	share->opttotal = 0;
}

static	void	put_info(int ac, char **av, t_list **list)
{
	int		i;
	t_list	*new;
	t_philo *share;

	i = 0;
	share = (t_philo *)malloc(sizeof(t_philo));
	init_share(share);
	while (i++ < ft_atoi(av[1]))
	{
		new = ft_lstnew((ULL)ft_atoi(av[1]), i);
		new->info->lifetime = (ULL)ft_atoi(av[2]);
		new->info->eattime = (ULL)ft_atoi(av[3]);
		new->info->naptime = (ULL)ft_atoi(av[4]);
		new->info->taken = get_time();
		new->info->status = 0;
		if (ac == 6)
		{
			new->info->option = (ULL)ft_atoi(av[5]);
			new->info->optown = 0;
		}
		else
			new->info->option = -1;
		new->share = share;
		insert_list(list, new);
	}
}

t_bool	init_philo(int ac, char **av, t_list **list)
{
	int		i;

	i = 1;
	if (ac != 5 && ac != 6)
		return FALSE;
	while (i < ac)
	{
		if (!av[i])
			return (FALSE);
		i++;
	}
	put_info(ac, av, list);
	return (1);
}

unsigned long long get_time(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) < 0)
		return -1;
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
