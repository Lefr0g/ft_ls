/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_print_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 15:59:52 by amulin            #+#    #+#             */
/*   Updated: 2016/08/24 16:13:26 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Subfunction for ls -l, used to generate a date string from ctime
*/

char	*ftls_gen_timestr(t_env *e, t_entry *d)
{
	char	*str;
	time_t	now;
	time_t	date;
	int		i;

	if (e->sort_time_val == 'u')
		date = d->st_atimespec.tv_sec;
	else if (e->sort_time_val == 'c')
		date = d->st_ctimespec.tv_sec;
	else
		date = d->st_mtimespec.tv_sec;
	now = time(NULL);
	if (now - date > 15811200 || date - now > 15811200)
	{
		str = ft_strdup(&ctime(&date)[4]);
		if (ft_strlen(str) == 26 && (i = 1))
			ft_strncpy(&str[7], &str[19], 6);
		else if (!(i = 0))
			ft_strncpy(&str[7], &str[15], 5);
		ft_bzero(&str[12 + i], 10);
	}
	else
		str = ft_strsub(ctime(&date), 4, 12);
	return (str);
}

#ifdef __APPLE__

/*
**	Print an entry with the -l option. Used for OSX.
*/

void	ftls_quick_ll_osx(t_env *e, t_entry *d)
{
	char			out[12];
	char			*path;

	path = ((d->prefix)) ? ft_strjoin(*(d->prefix), *(d->name)) :
		ft_strdup(*(d->name));
	ftls_decode_mode(d->st_mode, out);
	ftls_decode_extended_osx(out, path);
	ft_strdel(&path);
	ftls_quick_ll_sub_common(e, d, out);
}

#elif __linux__

/*
**	Print an entry with the -l option. Used for Linux.
*/

void	ftls_quick_ll_linux(t_env *e, t_entry *d)
{
	char			out[12];
	char			*path;

	path = ((d->prefix)) ? ft_strjoin(*(d->prefix), *(d->name)) :
		ft_strdup(*(d->name));
	ft_bzero(out, 12);
	ftls_decode_mode(d->st_mode, out);
	ft_strdel(&path);
	ftls_quick_ll_sub_common(e, d, out);
}

#endif

/*
**	Subfunction for both ftls_quick_ll functions, with identical behavior
**	on OSX and Linux
*/

void	ftls_quick_ll_sub_common(t_env *e, t_entry *d, char *out)
{
	char	*timebuf;

	out[11] = '\0';
	timebuf = ftls_gen_timestr(e, d);
	ft_putstr(out);
	ft_printf("%*d", e->maxcol[2] + 1, d->st_nlink);
	ft_printf(" %*s", -(e->maxcol[3] + 1), *(d->pw_name));
	ft_printf(" %*s", -(e->maxcol[4] + 1), *(d->gr_name));
	ftls_quick_ll_print_dev_or_size(e, d);
	ft_printf("%s ", timebuf);
	ft_strdel(&timebuf);
	ft_printf("%s", *(d->name));
	if ((d->st_mode & S_IFLNK) == S_IFLNK)
		ft_printf(" -> %s\n", *(d->linktarget));
	else
		ft_putchar('\n');
	e->print_initiated = 1;
}

/*
**	Subfunction for both ftls_quick_ll functions.
**	If the entry is a device, major and minor number will be printed. Otherwise,
**	the size of the entry will be printed.
*/

void	ftls_quick_ll_print_dev_or_size(t_env *e, t_entry *d)
{
	if (ftls_is_entry_device(d))
		ft_printf("%*d, %*d ", e->maxcol[6] + 2, major(d->st_rdev),
				e->maxcol[7], minor(d->st_rdev));
	else
	{
		if (!e->human)
		{
			if (!e->maxcol[8])
				ft_printf("%*d ", e->maxcol[5] + 1, d->st_size);
			else
				ft_printf("%*d ", e->maxcol[6] + e->maxcol[7] + 4, d->st_size);
		}
		else
			ft_printf("%6s ", *(d->size_str));
	}
}
