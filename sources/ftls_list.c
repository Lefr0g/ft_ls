/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 17:49:22 by amulin            #+#    #+#             */
/*   Updated: 2016/05/23 21:22:10 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** This function creates a new element in the directory entry list pointed to
** by 'alst', using lstat on the file or directory designated by 'name' and
** optional 'prefix' to fill the t_de structure within the new list element.
**
** TODO : Remplissage du subdir si pas de prefix, plus recursivite si -R
*/
void	ftls_add_entry(t_list **alst, t_env *e, char *name, char *prefix)
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
		ft_print_error(e->progname, path, errno);
		exit(2);
	}
	ft_strdel(&path);
	ftls_copy_details(&entry, &statbuf, name, prefix);
	lst_ptr = ft_lstnew(&entry, sizeof(t_de));
	if (*alst)
		ft_lstappend(alst, lst_ptr);
	else
		*alst = lst_ptr;

	// WIP
	ftls_manage_subdir(lst_ptr, &((t_de*)(lst_ptr->content))->subdir, e);

}

/*
** WIP
**
** Subfunction for ftls_add_entry().
** This function fills the subdir list whenever and only if needed.
** It contains the trigger for recursive population of dir lists.
*/
void	ftls_manage_subdir(t_list *current, t_list **subdir, t_env *e)
{
	t_de			*d;
	DIR 			*dirstream;
	struct dirent	*dirent;
	char			*prefix;

	d = current->content;
	if ((!d->prefix || e->recursive) && (d->st_mode & S_IFDIR) == S_IFDIR)
	{
		if (!(dirstream = opendir(d->d_name)))
		{
			ft_print_error(e->progname, d->d_name, errno);
			exit(1);
		}
		prefix = ft_strjoin(d->d_name, "/");
		while ((dirent = readdir(dirstream)))
			ftls_add_entry(subdir, e, dirent->d_name, prefix);
		ft_strdel(&prefix);
		if (closedir(dirstream))
		{
			ft_print_error(e->progname, d->d_name, errno);
			exit(1);
		}
	}
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

/*
** TODO : fix read error
*/
void	test_elemdel(void *ptr, size_t size)
{
	t_de	*d;

	d = ((t_list*)ptr)->content;
	if (d->subdir)
		ft_lstdel(&(d->subdir), &test_elemdel);
	if (d->prefix)
		ft_strdel(&d->prefix);
	ft_bzero(ptr, size);
	ft_memdel(&ptr);
}
