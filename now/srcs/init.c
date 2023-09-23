#include "../inc/philo.h"

static t_bool		init_share(t_philo *share)
{
	if (pthread_mutex_init((&share->prints), NULL) != 0 ||
	pthread_mutex_init((&share->inactive), NULL) != 0 ||
	pthread_mutex_init((&share->opt), NULL) != 0)
	{
		free(share);
		printf("\033[0;31mFailed to Init thread MUTEX\n");
		return (0);
	}
	share->dead = 0;
	share->record = get_time();
	share->opttotal = 0;
	return (1);
}

t_bool	init_info(int ac, char **av, t_list **list, t_philo *share)
{
	int	i;
	t_list *new;

	i = 0;
	while ((ULL)i++ <= (ULL)ft_atoi(av[1]))
	{
		new = ft_lstnew((ULL)ft_atoi(av[1]), i, av);
		// new->info->lifetime = (ULL)ft_atoi(av[2]);
		// new->info->eattime = (ULL)ft_atoi(av[3]);
		// new->info->naptime = (ULL)ft_atoi(av[4]);
		// new->info->taken = get_time();
		// new->info->status = 0;
		// new->info->optown = 0;
		if (!(validinfo(new)))
			return (0);
		if (ac == 6)
		{
			new->info->option = (ULL)ft_atoi(av[5]);
			if (new->info->option == 0)
			{
				free(new->info);
				free(new->share);
				free(new);
				printf("\033[0;31m🍑Option must be over ZER0🍑\n");
				return (0);
			}
		}
		else
			new->info->option = -1;
		new->share = share;
		insert_list(list, new);
	}
	return (1);
}

t_bool	put_info(int ac, char **av, t_list **list)
{
	t_philo *share;

	share = (t_philo *)malloc(sizeof(t_philo));
	if (!share)
		return (0);
	if(!init_share(share))
		return (0);
	if (!init_info(ac, av, list, share))
		return (0);
	return (1);
}
