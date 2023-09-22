#include "../inc/philo.h"

// static  t_bool  eveneat_half(t_list *list);
// static  t_bool  oddeat_half(t_list *list);

void    mutex(t_list *list, int onoff)
{
    if (onoff == 1)
        pthread_mutex_lock(&(list->fork));
    else if (onoff == 0)
        pthread_mutex_unlock(&(list->fork));
}

static  t_bool  eveneat_half(t_list *list)
{
    if (option(list))
      return (1);
    list->info->taken = get_time();
    if (moniterlife(list, list->info->eattime))
    {
        pthread_mutex_unlock(&(list->fork));
        pthread_mutex_unlock(&(list->next->fork));
        return (1);
    }
    mutex(list, 0);
    mutex(list->next, 0);
    if (switchoff(list))
      return (1);
    status(list, SLEEP);
    return (0);
}

t_bool  eveneat(t_list *list, int nrd)
{
	  mutex(list, 1);
    if (switchoff(list))
    {
		pthread_mutex_unlock(&(list->fork));
        return (1);
    }
    print_act(list, nrd, 0);
    mutex(list->next, 1);
    if (switchoff(list))
    {
		pthread_mutex_unlock(&(list->fork));
        pthread_mutex_unlock(&(list->next->fork));
        return (1);
    }
    print_act(list, nrd, 1);
    status(list, EAT);
    // if (option(list))
    // {
    //   return (1);
    // }
    // list->info->taken = get_time();
    if (eveneat_half(list))
        return (1);
    // if (moniterlife(list, list->info->eattime))
    // {
    //     pthread_mutex_unlock(&(list->fork));
    //     pthread_mutex_unlock(&(list->next->fork));
    //     return (1);
    // }
    // mutex(list, 0);
    // mutex(list->next, 0);
    // if (switchoff(list))
    // {
    //   return (1);
    // }
    // status(list, SLEEP);
   // return (0);
    
    return (0);
}

static  t_bool  oddeat_half(t_list *list)
{
    if (option(list))
      return (1);
    list->info->taken = get_time();
    if (moniterlife(list, list->info->eattime))
    {
        pthread_mutex_unlock(&(list->next->fork));
        pthread_mutex_unlock(&(list->fork));
        return (1);
    }
    mutex(list->next, 0);
    mutex(list, 0);
    if (switchoff(list))
      return (1);
    status(list, SLEEP);
    return (0);
}

t_bool  oddeat(t_list *list, int nrd)
{
	mutex(list->next, 1);
	print_act(list, nrd, 0);
    if (switchoff(list))
    {
		pthread_mutex_unlock(&(list->next->fork));
        return (1);
    }
    mutex(list, 1);
	if (switchoff(list))
    {
		pthread_mutex_unlock(&(list->next->fork));
        pthread_mutex_unlock(&(list->fork));
        return (1);
    }
    yield(list);
    print_act(list, nrd, 1);
    status(list, EAT);
    // if (option(list))
    // {
    //   return (1);
    // }
    // list->info->taken = get_time();
    if (oddeat_half(list))
        return (1);
    // if (moniterlife(list, list->info->eattime))
    // {
    //     pthread_mutex_unlock(&(list->next->fork));
    //     pthread_mutex_unlock(&(list->fork));
    //     return (1);
    // }
    // mutex(list->next, 0);
    // mutex(list, 0);
    // if (switchoff(list))
    // {
    //   return (1);
    // }
    // status(list, SLEEP);
    return (0);
}


// t_bool  eveneat(t_list *list, int nrd)
// {
//     mutex(list, 1);
//     if (switchoff(list))
//     {
// 		pthread_mutex_unlock(&(list->fork));
//         return (1);
//     }
//     print_act(list, nrd, 0);
//     mutex(list->next, 1);
//     if (switchoff(list))
//     {
// 		pthread_mutex_unlock(&(list->fork));
//         pthread_mutex_unlock(&(list->next->fork));
//         return (1);
//     }
//     print_act(list, nrd, 1);
//     status(list, EAT);
//     list->info->taken = get_time();
// 	  if (option(list))
//     {
//       return (1);
//     }
//     if (moniterlife(list, list->info->eattime))
//     {
//         pthread_mutex_unlock(&(list->fork));
//         pthread_mutex_unlock(&(list->next->fork));
//         return (1);
//     }
//     mutex(list, 0);
//     mutex(list->next, 0);
//     if (switchoff(list))
//       return (1);
//     status(list, SLEEP);
//     return (0);
// }

// t_bool  oddeat(t_list *list, int nrd)
// {
// 	mutex(list->next, 1);
//   print_act(list, nrd, 0);
// 	if (switchoff(list))
//     {
// 		pthread_mutex_unlock(&(list->next->fork));
//         return (1);
//     }
//     mutex(list, 1);
// 	if (switchoff(list))
//     {
// 		pthread_mutex_unlock(&(list->next->fork));
//         pthread_mutex_unlock(&(list->fork));
//         return (1);
//     }
//     yield(list);
//     print_act(list, nrd, 1);
//     status(list, EAT);
//     list->info->taken = get_time();
// 	  if (option(list))
//     {
//       return (1);
//     }
//     if (moniterlife(list, list->info->eattime))
//     {
//         pthread_mutex_unlock(&(list->next->fork));
//         pthread_mutex_unlock(&(list->fork));
//         return (1);
//     }
//     mutex(list->next, 0);
//     mutex(list, 0);
//     if (switchoff(list))
//       return (1);
//     status(list, SLEEP);
//     return (0);
// }
