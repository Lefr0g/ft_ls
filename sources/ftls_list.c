/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 17:49:22 by amulin            #+#    #+#             */
/*   Updated: 2016/05/23 18:21:46 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** This function creates a new element in the directory entry list pointed to
** by 'alst', using lstat on the file or directory designated by 'name' and
** optional 'prefix' to fill the t_de structure within the new list element.
**
** TODO : Remplissage du subdir si pas de prefix, plus recursivite si -R
**		  Remplacer argument progname pas env
*/
void	ftls_add_entry(t_list **alst, char *progname, char *name, char *prefix)
{
	t_de		entry;
	struct stat	statbuf;
	char		*path;
	t_list		*lst_ptr;

	lst_ptr = NULL;
	if (!name || ft_strlen(name) > 255)
		exit(1);
	path = (prefix) ? ft_strjoin(prefix, name) : ft_strdup(name);
	if (lstat(path, &statbuf))
	{
		ft_print_error(progname, path, errno);
		exit(2);
	}
	ft_strdel(&path);
	ftls_copy_details(&entry, &statbuf, name, prefix);
	lst_ptr = ft_lstnew(&entry, sizeof(t_de));
	if (*alst)
		ft_lstappend(alst, lst_ptr);
	else
		*alst = lst_ptr;
}

/*
** Subfunction for ftls_add_entry
*/
void	ftls_copy_details(t_de *dst, struct stat *src, char *name, char *prefix)
{
	ftls_init_details(dst);
	dst->d_ino = src->st_ino;
	dst->d_namelen = ft_strlen(name);
	ft_strcpy(dst->d_name, name);
	dst->st_mode = src->st_mode;
	dst->st_nlink = src->st_nlink;
	dst->st_uid = src->st_uid;
	dst->st_gid = src->st_gid;
	dst->st_atimespec = src->ATIME;
	dst->st_mtimespec = src->MTIME;
	dst->st_ctimespec = src->CTIME;
	dst->st_size = src->st_size;
	if (prefix)
		dst->prefix = ft_strdup(prefix);
}

void	test_elemdel(void *ptr, size_t size)
{
	ft_bzero(ptr, size);
	ft_memdel(&ptr);
}
