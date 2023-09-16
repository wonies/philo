#include "../inc/philo.h"

t_list	*ft_lstnew(int num, int idx)
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
		free(new);
		return (NULL);
	}
	new->info->cnt = num;
	new->info->idx = idx;
	new->info->lock = 0;
	new->info->moniter = 0;
	return (new);
}

void insert_list(t_list** head, t_list *new_node)
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
	int			sign;
	int			res;
	size_t		i;

	sign = 1;
	res = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (sign * res);
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
