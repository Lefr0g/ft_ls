/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 17:49:22 by amulin            #+#    #+#             */
/*   Updated: 2016/06/01 21:13:43 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// A REFAIRE

#include "ft_ls.h"

/*
** This function creates a new element in the directory entry list pointed to
** by 'alst', using lstat on the file or directory designated by 'name' and
** optional 'prefix' to fill the t_de structure within the new list element.
**
** TODO : Remplissage du subdir si pas de prefix, plus recursivite si -R
*/
int		ftls_add_entry(t_list **alst, t_env *e, char *name, char *prefix)
{
	t_de		entry;
	struct stat	statbuf;
	char		*path;
	t_list		*lst_ptr;

	lst_ptr = NULL;
	if (!name || ft_strlen(name) > 255)
		return (1);
	path = (prefix) ? ft_strjoin(prefix, name) : ft_strdup(name);
	if (lstat(path, &statbuf))
	{
		ft_print_error(e->progname, path, errno);
		ft_printf("(Error from lstat)\n");
		ft_strdel(&path);
		return (1);
	}
	ft_strdel(&path);
	ftls_copy_details(&entry, &statbuf, name, prefix);
	lst_ptr = ft_lstnew(&entry, sizeof(t_de));
	if (*alst)
		ft_lstappend(alst, lst_ptr);
	else
		*alst = lst_ptr;

//	ftls_copy_navpointers(lst_ptr);  // experimental


	// TODO
	// Ajouter ici (en amont de la recursivite) les fonctions pour :
	// 		- Tri
	// 		- Affichage

	if (prefix)
		ftls_quick_ll(e, &entry);
	else
		ft_printf("%s:\n", name);

	ftls_manage_subdir(lst_ptr, &((t_de*)(lst_ptr->content))->subdir, e);
	return (0);
}

int		ftls_add_entry_v2(t_list **alst, t_env *e, char *name, char *prefix)
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
	ftls_copy_details_v2(&entry, &statbuf, name, prefix);
	lst_ptr = ft_lstnew(&entry, sizeof(t_entry));
	if (*alst)
		ft_lstappend(alst, lst_ptr);
	else
		*alst = lst_ptr;
	return (0);
}

/*
** WIP
**
** Subfunction for ftls_add_entry().
** This function fills the subdir list whenever and only if needed.
** It contains the trigger for recursive population of dir lists.
*/
int		ftls_manage_subdir(t_list *current, t_list **subdir, t_env *e)
{
	t_de			*d;
	DIR 			*dirstream;
	struct dirent	*dirent;
	char			*prefix;
	char			*path;

	d = current->content;
	if ((d->st_mode & S_IFDIR) == S_IFDIR && (!d->prefix || (e->recursive &&
					ft_strcmp(d->d_name, ".") && ft_strcmp(d->d_name, ".."))))
	{
		if (d->prefix)
			path = ft_strjoin(d->prefix, d->d_name);
		else
			path = ft_strdup(d->d_name);
		if (!(dirstream = opendir(path)))
		{
			ft_print_error(e->progname, d->d_name, errno);
			ft_printf("(Error from opendir)\n");
			ft_strdel(&path);
			return (1);
		}
		prefix = ft_strjoin(path, "/");
		ft_strdel(&path);
		while ((dirent = readdir(dirstream)))
			ftls_add_entry(subdir, e, dirent->d_name, prefix);
		ft_strdel(&prefix);
		if (closedir(dirstream))
		{
			ft_print_error(e->progname, d->d_name, errno);
			return (1);
		}
		ft_putchar('\n'); // TEMPORARY - To separate dirs in ls -l mode
	}
	return (0);
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

void	ftls_copy_details_v2(t_entry *dst, struct stat *src, char *name, char *prefix)
{
	ftls_init_entry(dst);
	dst->name = ft_strdup(name);
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
** This function is designed for use as a parameter for ft_lstdel()
*/
void	ftls_elemdel(void *ptr, size_t size)
{
	t_entry	*d;

	d = (t_entry*)ptr;
//	if (d->subdir)
//		ft_lstdel(&(d->subdir), &ftls_elemdel);
	if (d->name)
		ft_strdel(&d->name);
	if (d->prefix)
		ft_strdel(&d->prefix);
	ft_bzero(ptr, size);
	ft_memdel(&ptr);
}

