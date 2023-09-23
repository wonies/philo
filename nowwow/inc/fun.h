/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonie <wonie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 18:09:12 by wonie             #+#    #+#             */
/*   Updated: 2023/09/23 18:24:59 by wonie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUN_H
# define FUN_H

/* init.c */
t_bool	put_info(int ac, char **av, t_list **list);

/* valid.c */
t_bool	validzero(int ac, char **av, t_philo *share);
t_bool	validinfo(t_list *list, t_philo *share);
t_bool	validphilo(int ac, char **av);
t_bool	destroy_mutex(t_list *list, int idx);

/* utils.c */
t_bool	print_act(t_list *list, int nrd, int warn);
t_bool	status(t_list *list, int active);
t_bool	option(t_list *list);
t_bool	switchoff(t_list *list);
void	freeres(t_list **list);

/* time.c */
ULL		get_time(void);
t_bool	moniterlife(t_list *list, ULL times);
t_bool	died(t_list *list, ULL timz);

/* life.c */
t_bool	to_mutex(t_list **list);

/* table.c */
void	*routine(void *arg);

/* eat.c */
t_bool	oddeat(t_list *list, int nrd);
t_bool	eveneat(t_list *list, int nrd);
void	mutex(t_list *list, int onoff);

/* eatutils.c */
t_bool	yield(t_list *list);

/* setting.c */
t_list	*ft_lstnew(int num, int idx, char **av);
void	insert_list(t_list **head, t_list *new_node);
int		ft_atoi(const char *str);

#endif