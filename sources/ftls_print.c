/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 15:59:52 by amulin            #+#    #+#             */
/*   Updated: 2016/06/17 19:08:58 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
 *	Temporary
*/
void	ftls_quick_ll(t_env *e, t_entry *d)
{
	char			out[12];
#if LEAKY_STDLIB_ENABLE
	char			*timebuf;
	struct passwd	*passbuf;
	struct group	*groupbuf;
#endif
	char			*path;
	acl_t			aclbuf;

	(void)e;
	path = ((d->prefix)) ? ft_strjoin(*(d->prefix), *(d->name)) :
		ft_strdup(*(d->name));
	ft_bzero(out, 12);
	ftls_decode_type(d->st_mode, out);
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
#if LEAKY_STDLIB_ENABLE
	// Valgrind doesn't like these function calls at all..
	timebuf = ft_strsub(ctime(&(d->MTIME.tv_sec)), 4, 12);
	passbuf = getpwuid(d->st_uid);
	groupbuf = getgrgid(d->st_gid);
#endif 
	ft_putstr(out);
	ft_printf("%3d ", d->st_nlink);
#if LEAKY_STDLIB_ENABLE
	ft_printf("%s\t%s\t", passbuf->pw_name, groupbuf->gr_name);
#endif
	ft_printf("%5d ", d->st_size);
#if LEAKY_STDLIB_ENABLE
	ft_printf("%s ", timebuf);
	ft_strdel(&timebuf);
#endif
	ft_printf("%s", *(d->name));
	if ((d->st_mode & S_IFLNK) == S_IFLNK)
		ft_printf(" -> %s\n", *(d->linktarget));
	else
		ft_putchar('\n');
//	ft_printf("blocks = %d\n", d->st_blocks);
	e->print_initiated = 1;
}

/*
**	Bidouille rapide pour affichage en colonnes propre
**	TODO: modifier l'ordre d'affichage ! Zigzag vertical, pas horizontal !
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
	if (e->showlist)
		ftls_quick_ll(e, entptr);
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
