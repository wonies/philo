/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonie <wonie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:01:27 by wonie             #+#    #+#             */
/*   Updated: 2023/09/23 17:15:14 by wonie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_list	*list;

	list = NULL;
	if (!(validphilo(ac, av)) || !(put_info(ac, av, &list)))
		return (1);
	if (!to_mutex(&list))
		return (1);
	destroy_mutex(list, 0);
	freeres(&list);
	return (0);
}
