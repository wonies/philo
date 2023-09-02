# ifndef PHILO_H
# define PHILO_H

#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_info
{
	int num;
	int die;
	int eat;
	int sleep;
	int eattime;
} t_info;

typedef struct s_list
{
	struct s_list	*prev;
	struct s_list	*next;
	t_info *info;
	pthread_mutex_t fork;
	pthread_t niche;
	int		index;
	int		flag;
	int		not_eat;
	int		num;
}	t_list;

typedef struct s_philo
{
	t_info *info;
	t_list *list;
	pthread_t thread;
	pthread_mutex_t mutex;
} t_philo;

int	ft_atoi(const char *str);
t_list	*ft_lstnew(int num);
void	ft_lstadd_back(t_list **lst, t_list *new);

# endif