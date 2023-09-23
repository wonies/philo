/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonie <wonie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:01:29 by wonie             #+#    #+#             */
/*   Updated: 2023/09/23 17:16:42 by wonie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_list	*ft_lstnew(int num, int idx, char **av)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->prev = NULL;
	new->next = NULL;
	new->info = (t_info *)malloc(sizeof(t_info));
	if (!new->info)
	{
		free(new->info);
		free(new);
		return (NULL);
	}
	new->info->cnt = num;
	new->info->idx = idx + 1;
	new->info->lifetime = (ULL)ft_atoi(av[2]);
	new->info->eattime = (ULL)ft_atoi(av[3]);
	new->info->naptime = (ULL)ft_atoi(av[4]);
	new->info->taken = get_time();
	new->info->status = 0;
	new->info->optown = 0;
	return (new);
}

void	insert_list(t_list **head, t_list *new_node)
{
	if (!new_node || !head)
		return ;
	if (!*head)
	{
		*head = new_node;
		new_node->prev = new_node;
		new_node->next = new_node;
	}
	else
	{
		new_node->next = *head;
		new_node->prev = (*head)->prev;
		(*head)->prev->next = new_node;
		(*head)->prev = new_node;
	}
}

int	ft_atoi(const char *str)
{
	int			res;
	size_t		i;
	long		num;

	num = 2147483647;
	res = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		i++;
		if (res > num || res <= 0)
			return (0);
	}
	return (res);
}

int	ft_lstsize(t_list **lst)
{
	int		size;
	t_list	*cur;

	size = 0;
	cur = *lst;
	while (1)
	{
		size++;
		cur = cur->next;
		if (cur == *lst)
			break ;
	}
	return (size);
}
