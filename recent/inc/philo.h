# ifndef PHILO_H
# define PHILO_H

#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

// #define STARVE 
// #define EAT
// #define SLEEP

typedef enum e_status
{
	STARVE,
	EAT,
	SLEEP,
	DEATH,
} t_status;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_info
{
	int 			cnt;
	int				lifetime;
	int 			eattime;
	int 			naptime;
	int 			option;
	int				idx;
	t_bool			lock;
	t_bool			moniter;
	unsigned long long	taken;
	t_status		status;
} t_info;

typedef struct s_philo
{
	pthread_mutex_t prints;
	pthread_mutex_t circle;
	int				start;
	int				times;
	int				dead;
	unsigned long long			record;
	unsigned long long			alive;
	
} t_philo;

typedef struct s_list
{
	struct s_list	*prev;
	struct s_list	*next;
	pthread_t 		niche;
	pthread_mutex_t fork;
	pthread_mutex_t	active;
	t_info			*info;
	t_philo			*share;
}	t_list;


int	ft_atoi(const char *str);

t_list	*ft_lstnew(int num, int idx);
void	insert_list(t_list** head, t_list *new_node);
void	print_list(t_list **head);
int		ft_lstsize(t_list **lst);
unsigned long long get_time(void);
t_bool	get_fork(t_list **list);
unsigned long long get_time(void);
void	*routine(void *arg);
t_bool	init_philo(int ac, char **av, t_list **list);
t_bool	get_fork(t_list **list);
t_bool	moniterlife(t_list *list, unsigned long long times);
t_bool	dead(t_list *list);
t_bool	died(t_list *list, unsigned long long timz);
# endif