#include "../inc/philo.h"

static	t_bool	validinput(char *c);

t_bool	validphilo(int ac, char **av)
{
	int		i;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		printf("\033[0;31m❗️Not Valid Input Condition❗️\n");
		return (0);
	}
	while (i < ac)
	{
		if (!(validinput(av[i])))
		{
			printf("\033[0;31m🍉Not Valid Input Condition🍉\n");
			return (0);
		}
		i++;
	}
	return (1);
}


static	t_bool	validinput(char *c)
{
	while (*c)
	{
		if (!(*c >= '0' && *c <= '9') && !(*c == '+'))
			return (0);
		c++;
	}
	return (1);
}

t_bool	validinfo(t_list *list)
{
	t_bool	valid;

	valid = 1;
	if (list->info->cnt <= 0)
	{
		valid = 0;
		printf("\033[0;31m🍉Philosopher wasnt there🍉\n");
	}
	if (list->info->lifetime <= 0 || list->info->eattime <= 0 || \
	list->info->naptime <= 0)
	{
		valid = 0;
		printf("\033[0;31m🍉Not valid time🍉\n");
	}
	if (valid == 0)
	{
		free(list->share);
		free(list->info);
		free(list);
		return (0);
	}
	return (1);
}
