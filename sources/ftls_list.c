/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 17:49:22 by amulin            #+#    #+#             */
/*   Updated: 2016/07/26 19:06:45 by amulin           ###   ########.fr       */
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
	if (ftls_is_entry_showable(e, &entry) && (e->atleastonetoshow = 1))
		e->totalblocks += entry.st_blocks;
	if (e->showlist && ftls_is_entry_showable(e, &entry))
		ftls_get_column_metadata(e, &entry);
	if ((entry.st_mode & S_IFLNK) == S_IFLNK)
		ftls_get_linktarget(&entry, path);
	ft_strdel(&path);
	lst_ptr = ft_lstnew(&entry, sizeof(t_entry));
	*alst ? ft_lstappend(alst, lst_ptr) : (*alst = lst_ptr);
	e->col_len = ft_getmax(e->col_len,
			ft_getmin(ft_strlen(name), e->termwidth));
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
**	This subfunction for ftls_add_entry manages user and group names copying,
**	and falls back to the respective uid or gid in case of error with
**	getpwuid or getgrgid function calls.
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
		ftls_gen_size_str(e, dst);
	}
}

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
		if (e->sort_time)
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
	ft_printf("CHECK A\n");
	if (!e->sort_none)
	{
		ft_printf("CHECK B\n");
		ft_lstsort(list, (void*)&(entptr->name) - (void*)entptr,
				&ftls_compare_str_linux);
/*		if (e->sort_time)
			ft_lstsort(list, (void*)&(entptr->st_time_ptr) - (void*)entptr,
					&FTLS_COMPARE_DATE);
		if (e->sort_size)
			ft_lstsort(list, (void*)&(entptr->st_size_ptr) - (void*)entptr,
					&ftls_compare_size);
		if (e->reverse)
			ft_lstflip(list);
			*/
//		if (e->iscli)
//			ft_lstsort(&e->lst, (void*)&entptr->st_mode_ptr - (void*)entptr,
//					&ftls_compare_type);
	}
}
