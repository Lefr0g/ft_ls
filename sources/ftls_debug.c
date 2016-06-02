/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 16:49:17 by amulin            #+#    #+#             */
/*   Updated: 2016/06/01 19:30:19 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

///	Verification du classement des arguments par le parseur
void	ftls_debug_show_args(t_env *e)
{
	int	i;

	ft_printf("Terminal width = %d\n", e->termwidth);
	ft_putstr("Printing sorted program arguments:\n");
	ft_putstr(">>> Options:\n");
	i = -1;
	while (e->cli_option[++i])
	{
		ft_printf("\tOption %d = %s\n", i, e->cli_option[i]);
	}
	ft_putstr(">>> Files, directories or bad arguments:\n");
	i = -1;
	while (e->cli_notopt[++i])
	{
		ft_printf("\tNon-option %d = %s\n", i, e->cli_notopt[i]);
	}
}

void	ftls_debug_show_list(t_list *lst)
{
	int		i;
	t_de	*content;

	ft_putendl("************************************************************");
	ft_printf("Printing list content. List address = %p :\n", lst);
	i = 0;
	while (lst)
	{
		content = lst->content;
		ft_printf("List elem %d, inode = %d\n", i, content->d_ino);
		ft_printf("Name = \033[32m%s\033[0m, namelen = %d\n",
				content->d_name, content->d_namelen);
		ft_printf("Size = %d\n", content->st_size);
		ft_printf("Prefix = \033[34m%s\033[0m\n", content->prefix);
		ft_printf("Mode = %b\n", content->st_mode);
		ft_printf("nlink = %d\n", content->st_nlink);
		ft_printf("uid = %d\n", content->st_uid);
		ft_printf("gid = %d\n", content->st_uid);
		ft_printf("atimespec = %d\n", content->st_atimespec);
		ft_printf("mtimespec = %d\n", content->st_mtimespec);
		ft_printf("ctimespec = %d\n", content->st_ctimespec);
		ft_printf("Subdir address is %p\n", content->subdir);
		if (content->subdir)
			ftls_debug_show_list(content->subdir);
		ft_putendl("*********************************************************");
		lst = lst->next;
		i++;
	}
}

void	ftls_debug_show_options(t_env *e)
{
	ft_putendl("************************************************************");
	ft_printf("OPTION FLAGS________________________________________________\n");
	ft_printf("Show_all_nodot %hhd\tShow_all %4hhd\n", e->show_all_nodot,
			e->show_all);
	ft_printf("Recursive %6hhd\tReverse %5hhd\n", e->recursive, e->reverse);
	ft_printf("Sort_none %6hhd\tSort_size %3hhd\t\n",
			e->sort_none, e->sort_size);
	ft_printf("Sort_timemod %3hhd\tHuman %7hhd\n", e->sort_timemod, e->human);
	ft_printf("Showinode %6hhd\tShowlist %4hhd\t\n", e->showinode, e->showlist);
	ft_printf("Oneperline %5hhd\n", e->oneperline);
	ft_putendl("************************************************************");
}
