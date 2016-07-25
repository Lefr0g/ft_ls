/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 15:59:52 by amulin            #+#    #+#             */
/*   Updated: 2016/06/21 14:24:40 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Subfunction for ls -l, used to generate a date string from ctime
*/
//char	*ftls_gen_timestr(time_t *date)
	
// timebuf = ftls_gen_timestr(&(d->FTLS_MTIME.tv_sec));

char	*ftls_gen_timestr(t_env *e, t_entry *d)
{
	char	*str;
	time_t	now;
	time_t	date;

	if (e->sort_time && e->sort_time_val == 'u')
		date = d->st_atimespec.tv_sec;
	else if (e->sort_time && e->sort_time_val == 'c')
		date = d->st_ctimespec.tv_sec;
	else
		date = d->st_mtimespec.tv_sec;
	now = time(NULL);
	if (now - date > 15811200 || date - now > 15811200)
	{
		str = ft_strdup(&ctime(&date)[4]);
		ft_strncpy(&str[7], &str[15], 5);
		ft_bzero(&str[12], 10);
	}
	else
		str = ft_strsub(ctime(&date), 4, 12);
	return (str);
}

#ifdef __APPLE__
/*
 *	Temporary
*/
void	ftls_quick_ll_osx(t_env *e, t_entry *d)
{
	char			out[12];
	char			*timebuf;
	char			*path;
	acl_t			aclbuf;

	(void)e;
	path = ((d->prefix)) ? ft_strjoin(*(d->prefix), *(d->name)) :
		ft_strdup(*(d->name));
	ft_bzero(out, 12);
	FTLS_DECODE_TYPE(d->st_mode, out);
	ftls_decode_access_rights(d->st_mode, out);
	if ((d->st_mode & S_ISVTX) == S_ISVTX)
		out[9] = 't';
	if (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0)
		out[10] = '@';
	else if ((aclbuf = acl_get_file(path, ACL_TYPE_EXTENDED)))
	{
		out[10] = ('+');
		acl_free(aclbuf);
	}
	else
		out[10] = ' ';
	ft_strdel(&path);
	out[11] = '\0';
	
	timebuf = ftls_gen_timestr(e, d);
	errno = 0;

	ft_putstr(out);
	ft_printf("%*d", e->maxcol[2] + 1, d->st_nlink);

	ft_printf(" %*s", -(e->maxcol[3] + 1), *(d->pw_name));
	ft_printf(" %*s", -(e->maxcol[4] + 1), *(d->gr_name));
	
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
		{
			ft_printf("%6s ", *(d->size_str));
		}
	}
	ft_printf("%s ", timebuf);
	ft_strdel(&timebuf);
	ft_printf("%s", *(d->name));
	if ((d->st_mode & S_IFLNK) == S_IFLNK)
		ft_printf(" -> %s\n", *(d->linktarget));
	else
		ft_putchar('\n');
//	ft_printf("blocks = %d\n", d->st_blocks);
	e->print_initiated = 1;
}
#elif __linux__
/*
 *	Temporary
*/
void	ftls_quick_ll_linux(t_env *e, t_entry *d)
{
	char			out[12];
	char			*timebuf;
	char			*path;

	(void)e;
	path = ((d->prefix)) ? ft_strjoin(*(d->prefix), *(d->name)) :
		ft_strdup(*(d->name));
	ft_bzero(out, 12);
	FTLS_DECODE_TYPE(d->st_mode, out);
	ftls_decode_access_rights(d->st_mode, out);
	if ((d->st_mode & S_ISVTX) == S_ISVTX)
		out[9] = 't';
	out[10] = ' ';
	ft_strdel(&path);
	out[11] = '\0';
	
	timebuf = ftls_gen_timestr(e, d);
	errno = 0;

	ft_putstr(out);
	ft_printf("%*d", e->maxcol[2] + 1, d->st_nlink);

	ft_printf(" %*s", -(e->maxcol[3] + 1), *(d->pw_name));
	ft_printf(" %*s", -(e->maxcol[4] + 1), *(d->gr_name));
	
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
		{
			ft_printf("%6s ", *(d->size_str));
		}
	}
	ft_printf("%s ", timebuf);
	ft_strdel(&timebuf);
	ft_printf("%s", *(d->name));
	if ((d->st_mode & S_IFLNK) == S_IFLNK)
		ft_printf(" -> %s\n", *(d->linktarget));
	else
		ft_putchar('\n');
//	ft_printf("blocks = %d\n", d->st_blocks);
	e->print_initiated = 1;
}
#endif

/*
**	Bidouille rapide pour affichage en colonnes propre
**	TODO: modifier l'ordre d'affichage : Zigzag vertical, pas horizontal
**		-> Abandon : investissement en temps necessaire trop important.
*/

void	ftls_print_name(t_env *e, char *name)
{
	int	spaces;
	int	i;
	
	if (e->oneperline)
	{
		ft_putstr(name);
		ft_putchar('\n');
	}
	else
	{
		i = -1;
//		ft_printf("\033[35m|\033[0m");
//		ft_printf("\033[35me->linelen = %d\033[0m", e->line_len);
		if (e->line_len + (int)ft_strlen(name) < e->termwidth)
		{
			ft_putstr(name);
			e->line_len += ft_strlen(name);
		}
		else
		{
			ft_putchar('\n');
			ft_putstr(name);
			e->line_len = ft_strlen(name);
		}
		spaces = e->col_len - ft_strlen(name) + 1;
//		ft_printf("\033[35mspaces = %d\033[0m", spaces);
		while (++i < spaces && e->line_len < e->termwidth)
		{
			ft_putchar(' ');
			e->line_len++;
		}
	}
//	ft_printf("e->linelen = %d\n", e->line_len);
}

/*
** Path concatenation from prefix and name
** Gestion affichage premiere ligne (espacement et path)
*/

char	*ftls_process_path(t_env *e, char *name, char *prefix)
{
	char	*buf;
	char	*path;

	if (!e->cli_notopt[0])
		buf = (prefix) ? ft_strjoin(prefix, name) : ft_strdup(".");
	else
		buf = (prefix) ? ft_strjoin(prefix, name) : ft_strdup(name);
	if (ft_strcmp(buf, "/"))
		path = ft_strjoin(buf, "/");
	else
		path = ft_strdup(buf);
	if (e->print_initiated)
		ft_putchar('\n');

	if (e->cli_notopt[1] || (e->recursive && prefix))
		ft_printf("%s:\n", buf);
	ft_strdel(&buf);
	return (path);
}

void	ftls_print_dir(t_env *e, t_list *subdir)
{
	t_list	*ptr;
	t_entry	*entptr;

	ptr = subdir;
	while (ptr)
	{
		entptr = ptr->content;
		if (ftls_is_entry_showable(e, entptr))
			ftls_print_entry(e, entptr);
		else
			if (!ptr->prev)
				e->print_initiated = 0;
		ptr = ptr->next;
	}
	e->line_len = 0;
	ftls_manage_spacing(e);
	e->print_initiated = 1;
}

void	ftls_print_entry(t_env *e, t_entry *entptr)
{
	if (e->showinode)
		ft_printf("%*d ", e->maxcol[0], entptr->st_inode);
	if (e->showlist)
	{
		FTLS_PRINT_LISTED(e, entptr);
		// TEMPORARY
	//	ft_printf("\033[32mmax col %d %d %d %d %d %d\n\033[0m", e->maxcol[0],
	//			e->maxcol[1], e->maxcol[2], e->maxcol[3], e->maxcol[4],
	//			e->maxcol[5]);
	}
	else
		ftls_print_name(e, *(entptr->name));
	e->print_initiated = 1;
}

void	ftls_manage_spacing(t_env *e)
{
	if (!e->oneperline && !e->showlist && e->print_initiated)
	{
		ft_putchar('\n');
		
	//	ft_printf("\nBD check\n");
	}
}
