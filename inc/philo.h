# ifndef PHILO_H
# define PHILO_H

#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_info
{
	int cnt;
	int	lifetime;
	int eattime;
	int naptime;
	int option;
	int	idx; 
	pthread_mutex_t prints;
	pthread_mutex_t sleeping;
	pthread_mutex_t thinking;
} t_info;


// typedef struct s_philo
// {
// 	pthread_mutex_t prints;
// 	t_info			*info;
// } t_philo;

typedef struct s_list
{
	struct s_list	*prev;
	struct s_list	*next;
	pthread_t 		niche;
	pthread_mutex_t fork;
	t_info			*info;
	int				use;
	int				status;
}	t_list;


int	ft_atoi(const char *str);

t_list	*ft_lstnew(t_list **list, int num, int idx);
void	ft_lstadd_back(t_list **lst, t_list *new);
void print_list(t_list **head);
void insert_list(t_list** head, t_list *new_node);
int	ft_lstsize(t_list **lst);

# endif