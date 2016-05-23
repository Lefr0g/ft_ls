/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 16:49:17 by amulin            #+#    #+#             */
/*   Updated: 2016/05/23 16:45:05 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

///	Verification du classement des arguments par le parseur
void	ftls_debug_show_args(t_env *e)
{
	int	i;

	ft_putstr("\nPrinting sorted program arguments:\n");
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

	i = 0;
	while (lst)
	{
		content = lst->content;
		ft_printf("List elem %d, inode = %d\n", i, content->d_ino);
		ft_printf("Name = %s, namelen = %d\n", content->d_name, content->d_namelen);
		ft_printf("Size = %d\n", content->st_size);
		ft_printf("Prefix = %s\n", content->prefix);
		ft_printf("Mode = %b\n", content->st_mode);
		ft_printf("nlink = %d\n", content->st_nlink);
		ft_printf("uid = %d\n", content->st_uid);
		ft_printf("gid = %d\n", content->st_uid);
		ft_printf("atimespec = %d\n", content->st_atimespec);
		ft_printf("mtimespec = %d\n", content->st_mtimespec);
		ft_printf("ctimespec = %d\n", content->st_ctimespec);
		ft_printf("Subdir address is %p\n", content->subdir);
		
		ft_putendl("*********************************************************");
		lst = lst->next;
		i++;
	}
}
