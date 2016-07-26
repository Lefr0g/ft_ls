/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 16:49:17 by amulin            #+#    #+#             */
/*   Updated: 2016/07/26 13:25:03 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Verification du classement des arguments par le parseur
*/

void	ftls_debug_show_args(t_env *e)
{
	int	i;

	ft_putendl("************************************************************");
	ft_printf("Terminal width = %d\n", e->termwidth);
	ft_putstr("Printing sorted program arguments:\n");
	ft_putstr(">>> Options:\n");
	i = -1;
	while (e->cli_option[++i])
	{
		ft_printf("\tOption %d = %s\n", i, e->cli_option[i]);
	}
	ft_putstr(">>> Valid files or directories:\n");
	i = -1;
	while (e->cli_notopt[++i])
	{
		ft_printf("\tNon-option %d = %s\n", i, e->cli_notopt[i]);
	}
}

void	ftls_debug_show_entry(t_entry *content)
{
	if (content->name)
		ft_printf("Name = \033[32m%s\033[0m\n", *(content->name));
	ft_printf("Size = %d\n", content->st_size);
	if (content->prefix)
		ft_printf("Prefix = \033[34m%s\033[0m\n", *(content->prefix));
	ft_printf("check\n");
	ft_printf("Mode = %b\n", content->st_mode);
	ft_printf("nlink = %d\n", content->st_nlink);
	ft_printf("uid = %d\n", content->st_uid);
	ft_printf("gid = %d\n", content->st_gid);
	ft_printf("atimespec = %d\n", content->st_atimespec);
	ft_printf("mtimespec = %d\n", content->st_mtimespec);
	ft_printf("ctimespec = %d\n", content->st_ctimespec);
	ft_putendl("*********************************************************");
}

void	ftls_debug_show_list(t_list *lst)
{
	int		i;
	t_entry	*content;

	ft_putendl("************************************************************");
	ft_printf("Printing list content. List address = %p :\n", lst);
	i = 0;
	while (lst)
	{
		content = lst->content;
		ftls_debug_show_entry(content);
		i++;
		lst = lst->next;
	}
}

void	ftls_debug_show_options(t_env *e)
{
	ft_putendl("************************************************************");
	ft_printf("OPTION FLAGS________________________________________________\n");
	ft_printf("Show_all_nodot %hhd\tShow_all %4hhd\n", e->show_all_nodot,
			e->show_all);
	ft_printf("Show_num_id %hhd\n", e->show_num_id);
	ft_printf("Recursive %6hhd\tReverse %5hhd\n", e->recursive, e->reverse);
	ft_printf("Sort_none %6hhd\tSort_size %3hhd\t\n",
			e->sort_none, e->sort_size);
	ft_printf("Human %7hhd\n", e->human);
	ft_printf("Sort_time = %hhd,\t\tSort_time_val = %c\n", e->sort_time,
			e->sort_time_val);
	ft_printf("Showinode %6hhd\tShowlist %4hhd\t\n", e->showinode, e->showlist);
	ft_printf("Oneperline %5hhd\n", e->oneperline);
	ft_printf("Followlink_cli %1hhd\tFollowlink_sub %4hhd\t\n",
			e->followlink_cli, e->followlink_sub);
	ft_putendl("************************************************************");
}
