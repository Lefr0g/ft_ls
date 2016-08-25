/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 16:45:18 by amulin            #+#    #+#             */
/*   Updated: 2016/08/25 16:34:30 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ftls_get_terminal_width(t_env *e)
{
	struct winsize	s_winsz;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &s_winsz) == -1)
	{
		ft_print_error(e->progname, "ioctl()", errno);
		return (-1);
	}
	return (s_winsz.ws_col);
}

int		ftls_isnavdot(char *name)
{
	if (!ft_strcmp(name, ".") || !ft_strcmp(name, ".."))
		return (1);
	return (0);
}

/*
**	This function checks if the option set is compatible with the file name.
**	Flags managed by this funtion: -a -A
*/

int		ftls_is_entry_showable(t_env *e, t_entry *entptr)
{
	char	*ptr;

	ptr = *(entptr->name);
	if (ptr[0] != '.' || (ptr[0] == '.' &&
				(e->show_all_nodot || e->show_all)))
		if (ptr[0] != '.' || !(ftls_isnavdot(ptr)
					&& (e->show_all_nodot)))
			return (1);
	return (0);
}

int		ftls_is_entry_device(t_entry *d)
{
	if ((d->st_mode & S_IFREG) == S_IFREG)
		return (0);
	if ((d->st_mode & S_IFLNK) != S_IFLNK &&
			((d->st_mode & S_IFCHR) == S_IFCHR
			|| (d->st_mode & S_IFBLK) == S_IFBLK))
		return (1);
	return (0);
}

/*
**	Checks if the entry is a dir that must be treated.
**	This entry can also be a symbolic link.
**	Invalid entries : sockets.
*/

int		ftls_is_entry_treatable(t_env *e, t_entry *entptr)
{
	DIR		*dir;

	if ((entptr->st_mode & S_IFSOCK) == S_IFSOCK
			|| (entptr->st_mode & S_IFBLK) == S_IFBLK)
		return (0);
	if ((entptr->st_mode & S_IFDIR) == S_IFDIR)
		return (1);
	if (e->followlink_cli && e->iscli && (entptr->st_mode & S_IFLNK) == S_IFLNK
		&& (dir = opendir(*(entptr->name))))
	{
		if (dir)
			closedir(dir);
		return (1);
	}
	if (e->followlink_sub && (entptr->st_mode & S_IFLNK) == S_IFLNK)
		return (1);
	return (0);
}
