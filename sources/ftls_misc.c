/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 16:45:18 by amulin            #+#    #+#             */
/*   Updated: 2016/06/14 18:40:08 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ftls_get_terminal_width(t_env *e)
{
	struct ttysize	s_ttsz;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &s_ttsz) == -1)
	{
		ft_print_error(e->progname, "ioctl()", errno);
		return (-1);
	}
	return (s_ttsz.ts_cols);
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

/*
**	Checks if the entry is a dir that must be treated.
**	This entry can also be a symbolic link.
**	Invalid entries : sockets.
**
**	A REFAIRE >> WIP
**
*/

int		ftls_is_entry_treatable(t_env *e, t_entry *entptr)
{
/*
	if (((entptr->st_mode & S_IFSOCK) != S_IFSOCK)
			&& ((entptr->st_mode & S_IFDIR) == S_IFDIR
				|| ((entptr->st_mode & S_IFLNK) == S_IFLNK
					&& ft_isdir(*(entptr->name), e->progname, 0)
					&& e->followlink)))
*/
	if ((entptr->st_mode & S_IFDIR) == S_IFDIR)
		return (1);
//		if (!((entptr->st_mode & S_IFLNK) == S_IFLNK && e->followlink))
//			return (1);
		
	if (e->followlink_cli && e->iscli && (entptr->st_mode & S_IFLNK) == S_IFLNK)
		return (1);
	if (e->followlink_sub && (entptr->st_mode & S_IFLNK) == S_IFLNK)
		return (1);
	return (0);
}
