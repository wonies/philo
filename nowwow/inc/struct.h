/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonie <wonie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 18:09:17 by wonie             #+#    #+#             */
/*   Updated: 2023/09/23 18:12:59 by wonie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "abbr.h"

typedef enum e_status
{
	STARVE,
	EAT,
	SLEEP,
}	t_status;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_info
{
	int			cnt;
	int			lifetime;
	ULL			eattime;
	ULL			naptime;
	int			option;
	int			idx;
	int			optown;
	t_status	status;
	ULL			taken;
}	t_info;

typedef struct s_philo
{
	pthread_mutex_t	prints;
	pthread_mutex_t	inactive;
	pthread_mutex_t	opt;
	int				opttotal;
	int				dead;
	ULL				record;
}	t_philo;

typedef struct s_list
{
	struct s_list	*prev;
	struct s_list	*next;
	pthread_t		niche;
	pthread_mutex_t	fork;
	pthread_mutex_t	active;
	t_info			*info;
	t_philo			*share;
}	t_list;

#endif