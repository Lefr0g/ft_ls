/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 17:49:22 by amulin            #+#    #+#             */
/*   Updated: 2016/06/28 18:15:17 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	This function creates a new element in the directory entry list pointed to
**	by 'alst', using lstat on the file or directory designated by 'name' and
**	optional 'prefix' to fill the t_de structure within the new list element.
**	If the entry is a symbolic link, the name of the target is copied.
**	Metadata for column layout are generated here
*/

int		ftls_add_entry(t_list **alst, t_env *e, char *name, char *prefix)
{
	struct stat	statbuf;
	char		*path;
	t_entry		entry;
	t_list		*lst_ptr;

	path = (prefix) ? ft_strjoin(prefix, name) : ft_strdup(name);
	if (ftls_get_file_status(e, &statbuf, &path))
		return (1);
	ftls_copy_details(&entry, &statbuf, name, prefix);
	if (e->showlist)
		ftls_copy_details_sub2(e, &entry, &statbuf);
	ftls_manage_time_ptr(e, &entry);
	//	Gestion des liens symboliques pour affichage -l
	if (ftls_is_entry_showable(e, &entry) && (e->atleastonetoshow = 1))
		e->totalblocks += entry.st_blocks;
	//	Gestion des metadatas de largeur de colonne
	if (e->showlist && ftls_is_entry_showable(e, &entry))
		ftls_get_column_metadata(e, &entry);
	if ((entry.st_mode & S_IFLNK) == S_IFLNK)
		ftls_get_linktarget(&entry, path);
	ft_strdel(&path);
	lst_ptr = ft_lstnew(&entry, sizeof(t_entry));
	if (*alst)
		ft_lstappend(alst, lst_ptr);
	else
		*alst = lst_ptr;
	e->col_len = ft_getmax(e->col_len,
			ft_getmin(ft_strlen(name), e->termwidth));
	return (0);
}

void	ftls_get_column_metadata(t_env *e, t_entry *d)
{
	int	i;

	if (e->showinode)
		if ((i = ft_nbrlen(d->st_inode)) > e->maxcol[0])
			e->maxcol[0] = i;
	e->maxcol[1] = 11;
	if ((i = ft_nbrlen(d->st_nlink)) > e->maxcol[2])
		e->maxcol[2] = i;
	if ((i = ft_strlen(*(d->pw_name))) > e->maxcol[3])
		e->maxcol[3] = i;
	if ((i = ft_strlen(*(d->gr_name))) > e->maxcol[4])
		e->maxcol[4] = i;
	if ((i = ft_nbrlen(d->st_size)) > e->maxcol[5])
		e->maxcol[5] = i;



}

/*
 *	This function is designed to act like the combination of ft_strlen on
 *	ft_itoa, but without all the memory allocation and processing involved.
 *	Its primary goal is to be fast and efficient.
 * 	To be added to libft
*/
int		ft_nbrlen(int nbr)
{
	int	div;
	int res;
	int	minus;

	if (nbr < 0)
		minus = 1;
	else
		minus = 0;

	div = 1000000000;
	res = 10;
	while (div)
	{
		if (nbr / div)
			return (res + minus);
		div /= 10;
		res--;
	}
	return (0);
}

void	ftls_get_linktarget(t_entry *dst, char *path)
{
	char	**buf;

	buf = ft_memalloc(sizeof(char**));
	*buf = ft_strnew(LINK_NAME_LEN);
	readlink(path, *buf, LINK_NAME_LEN);
	dst->linktarget = buf;
}

int		ftls_get_file_status(t_env *e, struct stat *statbuf, char **path)
{
	if ((e->followlink_cli && e->iscli) || e->followlink_sub)
	{
		if (stat(*path, statbuf))
		{
			ft_print_error(e->progname, *path, errno);
			ft_strdel(path);
			return (1);
		}
	}
	else if (lstat(*path, statbuf))
	{
		ft_print_error(e->progname, *path, errno);
		ft_strdel(path);
		return (1);
	}
	return (0);
}

/*
**	Subfunction for ftls_add_entry
*/

void	ftls_copy_details(t_entry *dst, struct stat *src, char *name,
		char *prefix)
{
	char	**buf;

	ft_bzero(dst, sizeof(t_entry));
	buf = ft_memalloc(sizeof(char**));
	if (!buf)
		exit(ft_print_error(NULL, NULL, errno));
	*buf = ft_strdup(name);
	if (!*(buf))
		exit(ft_print_error(NULL, NULL, errno));
	dst->name = buf;
	ftls_copy_details_sub1(dst, src);
	if (prefix)
	{
		buf = ft_memalloc(sizeof(char**));
		*buf = ft_strdup(prefix);
		dst->prefix = buf;
	}
}

/*
**	Subfunction, for norme compliance
*/
void	ftls_copy_details_sub1(t_entry *dst, struct stat *src)
{
	dst->st_inode = src->st_ino;
	dst->st_mode = src->st_mode;
	*(dst->st_mode_ptr) = dst->st_mode;
	dst->st_nlink = src->st_nlink;
	dst->st_rdev = src->st_rdev;
	dst->st_atimespec = src->FTLS_ATIME;
	dst->st_mtimespec = src->FTLS_MTIME;
	dst->st_ctimespec = src->FTLS_CTIME;
	dst->st_size = src->st_size;
	*(dst->st_size_ptr) = dst->st_size;
	dst->st_blocks = (int)src->st_blocks;
}

/*
 *	This subfunction for ftls_add_entry manages user and group names copying,
 *	and falls back to the respective uid or gid in case of error with
 *	getpwuid or getgrgid function calls.
*/
void	ftls_copy_details_sub2(t_env *e, t_entry *dst, struct stat *src)
{
	struct passwd	*passbuf;
	struct group	*groupbuf;
	char			**strbuf;

	dst->st_uid = src->st_uid;
	dst->st_gid = src->st_gid;
	passbuf = getpwuid(dst->st_uid);
	groupbuf = getgrgid(dst->st_gid);

	strbuf = (char**)malloc(sizeof(char*) * 2);
	if (e->showlist)
	{
		strbuf[0] = NULL;
		if (passbuf && !e->show_num_id)
			strbuf[0] = ft_strdup(passbuf->pw_name);
		else
			strbuf[0] = ft_itoa(dst->st_uid);
		dst->pw_name = &strbuf[0];
		strbuf[1] = NULL;
		if (groupbuf && !e->show_num_id)
			strbuf[1] = ft_strdup(groupbuf->gr_name);
		else
			strbuf[1] = ft_itoa(dst->st_gid);
		dst->gr_name = &strbuf[1];
	}
}

/*
 *	Manage time sort ptr
*/
void	ftls_manage_time_ptr(t_env *e, t_entry *dst)
{
	if (e->sort_time)
	{
		if (e->sort_time_val == 'c')
			*(dst->st_time_ptr) = dst->st_ctimespec;
		else if (e->sort_time_val == 'u')
			*(dst->st_time_ptr) = dst->st_atimespec;
		else	
			*(dst->st_time_ptr) = dst->st_mtimespec;
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
	if (d->linktarget)
	{
		ft_strdel(d->linktarget);
		ft_memdel((void**)&(d->linktarget));	
	}
	if (d->pw_name)
		ft_strdel(d->pw_name);
	if (d->gr_name)
		ft_strdel(d->gr_name);
	ft_memdel((void**)&(d->pw_name));
	ft_bzero(ptr, size);
	ft_memdel(&ptr);
}
