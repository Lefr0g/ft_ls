/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_sort_logic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 16:08:05 by amulin            #+#    #+#             */
/*   Updated: 2016/08/24 16:08:54 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Generic list sorting function, used in ftls_process.c
*/

void	ftls_manage_sorting_osx(t_env *e, t_list **list)
{
	t_entry	*entptr;

	entptr = (*list)->content;
	if (!e->sort_none)
	{
		ft_lstsort(list, (void*)&(entptr->name) - (void*)entptr,
				&ftls_compare_str);
		if (e->sort_time && !e->sort_size)
			ft_lstsort(list, (void*)&(entptr->st_time_ptr) - (void*)entptr,
					&FTLS_COMPARE_DATE);
		if (e->sort_size)
			ft_lstsort(list, (void*)&(entptr->st_size_ptr) - (void*)entptr,
					&ftls_compare_size);
		if (e->reverse)
			ft_lstflip(list);
		if (e->iscli)
			ft_lstsort(&e->lst, (void*)&entptr->st_mode_ptr - (void*)entptr,
					&ftls_compare_type);
	}
}

void	ftls_manage_sorting_linux(t_env *e, t_list **list)
{
	t_entry	*entptr;

	entptr = (*list)->content;
	if (!e->sort_none)
	{
		ft_lstsort(list, (void*)&(entptr->name) - (void*)entptr,
				&ftls_compare_str_linux);
		if (e->sort_time)
			ft_lstsort(list, (void*)&(entptr->st_time_ptr) - (void*)entptr,
					&FTLS_COMPARE_DATE);
		if (e->sort_size)
			ft_lstsort(list, (void*)&(entptr->st_size_ptr) - (void*)entptr,
					&ftls_compare_size);
		if (e->reverse)
			ft_lstflip(list);
	}
}
