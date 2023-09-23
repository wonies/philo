# ifndef PHILO_H
# define PHILO_H

#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define ULL unsigned long long

# define ACT_FORK	"has taken a fork"
# define ACT_EAT	"is eating"
# define ACT_NAP	"is sleeping"
# define ACT_THINK	"is thinking"
# define ACT_DIE	"died"

typedef enum e_status
{
	STARVE,
	EAT,
	SLEEP,
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
	ULL 			eattime;
	ULL 			naptime;
	int 			option;
	int				idx;
	int				optown;
	t_status		status;
	ULL				taken;
} t_info;

typedef struct s_philo
{
	pthread_mutex_t prints;
	pthread_mutex_t inactive;
	pthread_mutex_t opt;
	int				opttotal;
	int				dead;
	ULL				record;
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

t_list	*ft_lstnew(int num, int idx, char **av);
void	insert_list(t_list** head, t_list *new_node);
void	print_list(t_list **head);
int		ft_lstsize(t_list **lst);
unsigned long long get_time(void);
t_bool	get_fork(t_list **list);
unsigned long long get_time(void);
void	*routine(void *arg);
t_bool	get_fork(t_list **list);
t_bool	to_mutex(t_list **list);
t_bool	put_info(int ac, char **av, t_list **list);
t_bool	validphilo(int ac, char **av);
t_bool	validinfo(t_list *list);

t_bool  died(t_list *list, ULL timz);
t_bool    moniterlife(t_list *list, ULL times);
t_bool  eveneat(t_list *list, int nrd);
t_bool  oddeat(t_list *list, int nrd);
ULL get_time(void);
t_bool    moniterlife(t_list *list, ULL times);
t_bool  died(t_list *list, ULL timz);

t_bool  print_act(t_list *list, int nrd, int warn);
void    status(t_list *list, int active);
t_bool	option(t_list *list);
t_bool	switchoff(t_list *list);

t_bool	yield(t_list *list);

void    mutex(t_list *list, int onoff);

# endif