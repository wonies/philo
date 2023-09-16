#include "../inc/philo.h"

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

t_list	*ft_lstnew(t_list **list, int num, int idx)
{
	t_list	*new;

	(void)*list;
	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->prev = NULL;
	new->next = NULL;
	new->info = (t_info *)malloc(sizeof(t_info));
	if (new->info == NULL)
	{
		free(new); // 메모리 누수 방지
		return (NULL);
	}
	new->info->cnt = num;
	new->info->idx = idx;
	new->use = 0;
	return (new);
}

// #include <stdio.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	printf("-----\n");
	temp = *lst;
	printf("add back\n");
	if (!lst || !new)
	{
		printf("if 1\n");
		return ;
	}
	else if (!(*lst))
	{
		printf("if 2 s\n");
		(*lst) = new;
		(*lst)->prev = *lst;
		(*lst)->next = *lst;
		printf("if 2 e\n");
	}
	else
	{
		printf("if 3 s\n");
		while ((*lst)->next)
		{
			(*lst) = (*lst)->next;
			if ((*lst) == temp)
				break ;
		}
		(*lst)->next = new;
		new->next = temp;
		temp->prev = new;
		new->prev = *lst;
		(*lst) = temp;
		printf("if 3 e\n");
	}
}

void insert_list(t_list** head, t_list *new_node
{
    if (!new_node || !head)
		return ;
	if (*head == NULL)
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

static	void ft_lstadd(t_list **list, t_list *new)
{
	t_list	*head;
	t_list	*tail;

	if (*list)
	{
		head = *list;
		tail = (*list)->prev;
		tail->next = new;
		new->next = head;
		head->prev = new;
		new->prev = tail;
	}
	else
		*list = new;
}

int	ft_lstsize(t_list **lst)
{
	int	size;

	size = 0;
	t_list *cur = *lst;
	while (cur)
	{
		cur = cur->next;
		size++;
		if (cur == *lst)
			break ;
	}
	printf("check size FUNC\n");
	return (size);
}

void print_list(t_list **head)
{
	if (!*head)
		return;
	t_list *cur = *head;
	do {
		printf("-------print list------\n");
		printf("node data: %d\n", cur->info->idx);
		cur = cur->next;
	} while (cur != *head);
}

// void print_list(t_list **head)
// {
// 	printf("---------PRINT---------\n");
// 	// if (!head)
// 	// 	return ;
// 	t_list *cur = (*head)->next;
// 	while (cur != *head)
// 	{
// 		printf("-------print list------\n");
// 		printf("node data: %d\n", cur->info->idx);
// 		cur = cur->next;
// 	}
// }


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

