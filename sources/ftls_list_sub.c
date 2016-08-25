/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_list_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 17:49:22 by amulin            #+#    #+#             */
/*   Updated: 2016/08/25 16:39:07 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Get data needed for a clean list layout (-l option)
*/

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
	if (ftls_is_entry_device(d))
	{
		if ((i = ft_nbrlen((int)major(d->st_rdev))) > e->maxcol[6])
			e->maxcol[6] = i;
		if ((i = ft_nbrlen((int)minor(d->st_rdev))) > e->maxcol[7])
			e->maxcol[7] = i;
		e->maxcol[8] = 1;
	}
	else if ((i = ft_nbrlen(d->st_size)) > e->maxcol[5])
		e->maxcol[5] = i;
}

/*
**	Obtain the target of a symbolic link
*/

void	ftls_get_linktarget(t_entry *dst, char *path)
{
	char	**buf;

	buf = ft_memalloc(sizeof(char**));
	*buf = ft_strnew(LINK_NAME_LEN);
	readlink(path, *buf, LINK_NAME_LEN);
	dst->linktarget = buf;
}

/*
**	Access file data, ensure error management
*/

int		ftls_get_file_status(t_env *e, struct stat *statbuf, char **path)
{
	if ((e->followlink_cli && e->iscli) || e->followlink_sub)
	{
		if (stat(*path, statbuf))
		{
			if (lstat(*path, statbuf))
			{
				ft_print_error(e->progname, *path, errno);
				ft_strdel(path);
				return (1);
			}
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
**	Manage human-readable size output if needed
*/

void	ftls_gen_size_str(t_env *e, t_entry *d)
{
	char	**ptr;

	if (e->human)
	{
		ptr = (char**)malloc(sizeof(char*));
		*ptr = ft_humanize_size(d->st_size);
		d->size_str = ptr;
	}
}

/*
**	Manage time sort data pointer
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
