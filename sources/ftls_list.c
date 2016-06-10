/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 17:49:22 by amulin            #+#    #+#             */
/*   Updated: 2016/06/09 19:02:28 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** This function creates a new element in the directory entry list pointed to
** by 'alst', using lstat on the file or directory designated by 'name' and
** optional 'prefix' to fill the t_de structure within the new list element.
*/

int		ftls_add_entry(t_list **alst, t_env *e, char *name, char *prefix)
{
	struct stat	statbuf;
	char		*path;
	t_entry		entry;
	t_list		*lst_ptr;

	path = (prefix) ? ft_strjoin(prefix, name) : ft_strdup(name);
	if (lstat(path, &statbuf))
	{
		ft_print_error(e->progname, path, errno);
		ft_printf("(Error from lstat)\n");
		return (1);
	}
	ft_strdel(&path);
	ftls_copy_details(&entry, &statbuf, name, prefix);
	lst_ptr = ft_lstnew(&entry, sizeof(t_entry));
	if (*alst)
		ft_lstappend(alst, lst_ptr);
	else
		*alst = lst_ptr;
	return (0);
}

/*
** Subfunction for ftls_add_entry
*/

void	ftls_copy_details(t_entry *dst, struct stat *src, char *name,
		char *prefix)
{
	char	**testptr;

	ftls_init_entry(dst);
	testptr = ft_memalloc(sizeof(char**));
	if (!testptr)
		exit(ft_print_error(NULL, NULL, errno));
	*testptr = ft_strdup(name);
	if (!*(testptr))
		exit(ft_print_error(NULL, NULL, errno));
	dst->name = testptr;
	dst->st_mode = src->st_mode;
	*(dst->st_mode_ptr) = dst->st_mode;
	dst->st_nlink = src->st_nlink;
	dst->st_uid = src->st_uid;
	dst->st_gid = src->st_gid;
	dst->st_atimespec = src->ATIME;
	dst->st_mtimespec = src->MTIME;
	dst->st_ctimespec = src->CTIME;
	dst->st_size = src->st_size;
	if (prefix)
	{
		testptr = ft_memalloc(sizeof(char**));
		*testptr = ft_strdup(prefix);
		dst->prefix = testptr;
	}
}

/*
** This function is designed for use as a parameter for ft_lstdel()
*/

void	ftls_elemdel(void *ptr, size_t size)
{
	t_entry	*d;

	d = (t_entry*)ptr;
	if (d->name)
	{
		ft_strdel(d->name);
		ft_memdel((void**)&(d->name));
	}
	if (d->prefix)
	{
		ft_strdel(d->prefix);
		ft_memdel((void**)&(d->prefix));
	}
	ft_bzero(ptr, size);
	ft_memdel(&ptr);
}
