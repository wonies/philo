#include "incs/philo.h"

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

t_list	*ft_lstnew(int num)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->flag = 0;
	new->not_eat = 0;
	new->num = num;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = *lst;
	if (!lst || !new)
		return ;
	else if (!(*lst))
	{
		(*lst) = new;
		(*lst)->prev = *lst;
		(*lst)->next = *lst;
	}
	else
	{
		while ((*lst)->next)
			(*lst) = (*lst)->next;
		(*lst)->next = new;
		new->next = temp;
		temp->prev = new;
		new->prev = *lst;
		(*lst) = temp;
	}
}


void print_list(t_list *head)
{
	if (!head)
		return ;
	t_list *cur = head;
	while (cur != head)
	{
		printf("node data: %d\n", cur->index);
		cur = cur->next;
	}
}


// void ft_lstadd_back(t_list **lst, t_list *new)
// {
//     if (!lst || !new)
//         return;

//     if (!(*lst))
//     {
//         *lst = new;
//         new->prev = NULL; // 새로운 노드는 첫 번째 노드이므로 이전 노드가 없습니다.
//         return;
//     }

//     t_list *temp = *lst;
//     while (temp->next)
//         temp = temp->next;

//     temp->next = new;
//     new->prev = temp;
// }

