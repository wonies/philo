/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonie <wonie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:01:22 by wonie             #+#    #+#             */
/*   Updated: 2023/09/23 17:08:44 by wonie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static t_bool	init_share(t_philo *share)
{
	if (pthread_mutex_init(&share->prints, NULL) != 0 || \
	pthread_mutex_init(&share->inactive, NULL) != 0 || \
	pthread_mutex_init(&share->opt, NULL) != 0)
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
	int		i;
	t_list	*new;

	i = -1;
	if (!(validzero(ac, av, share)))
		return (0);
	while (++i < ft_atoi(av[1]))
	{
		new = ft_lstnew((ULL)ft_atoi(av[1]), i, av);
		if (!(validinfo(new, share)))
			return (0);
		if (ac == 6)
			new->info->option = (ULL)ft_atoi(av[5]);
		else
			new->info->option = -1;
		new->share = share;
		insert_list(list, new);
	}
	return (1);
}

t_bool	put_info(int ac, char **av, t_list **list)
{
	t_philo	*share;

	share = (t_philo *)malloc(sizeof(t_philo));
	if (!share)
		return (0);
	if (!init_share(share))
		return (0);
	if (!init_info(ac, av, list, share))
		return (0);
	return (1);
}
