/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 15:59:52 by amulin            #+#    #+#             */
/*   Updated: 2016/06/03 19:39:50 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
/*
 * TODO : leaks fix
 * 			- listxattr			->		0 leak,		0 error					OK
 * 			- acl_get_file		->		1 leak,		1 error		(./ft_ls /) OK
 * 			- ctime				-> >10,000 leaks,	3 errors				WIP
 * 			- getpwuid
 * 			- getgrgid
 *
*/
void	ftls_quick_ll(t_env *e, t_de *d)
{
	char			out[12];
# if LEAKY_STDLIB_ENABLE
	char			*timebuf;
	struct passwd	*passbuf;
	struct group	*groupbuf;
# endif
	char			*path;
	acl_t			aclbuf;

	(void)e;

	path = (d->prefix) ? ft_strjoin(d->prefix, d->d_name) : ft_strdup(d->d_name);
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

int					ft_getmax(int a, int b);
# if LEAKY_STDLIB_ENABLE
	// Valgrind doesn't like these function calls at all..
	timebuf = ft_strsub(ctime(&(d->MTIME.tv_sec)), 4, 12);
	passbuf = getpwuid(d->st_uid);
	groupbuf = getgrgid(d->st_gid);
# endif

	ft_putstr(out);
	ft_printf("%3d ", d->st_nlink);
# if LEAKY_STDLIB_ENABLE
	ft_printf("%s\t%s\t", passbuf->pw_name, groupbuf->gr_name);
# endif
	ft_printf("%5d ", d->st_size);

# if LEAKY_STDLIB_ENABLE
	ft_printf("%s ", timebuf);
	ft_strdel(&timebuf);
# endif
	ft_printf("%s\n", d->d_name);
}

/*
 *
*/
void	ftls_quick_ll_v2(t_env *e, t_entry *d)
{
	char			out[12];
# if LEAKY_STDLIB_ENABLE
	char			*timebuf;
	struct passwd	*passbuf;
	struct group	*groupbuf;
# endif
	char			*path;
	acl_t			aclbuf;

	(void)e;

	path = (d->prefix) ? ft_strjoin(d->prefix, d->name) : ft_strdup(d->name);
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

# if LEAKY_STDLIB_ENABLE
	// Valgrind doesn't like these function calls at all..
	timebuf = ft_strsub(ctime(&(d->MTIME.tv_sec)), 4, 12);
	passbuf = getpwuid(d->st_uid);
	groupbuf = getgrgid(d->st_gid);
# endif

	ft_putstr(out);
	ft_printf("%3d ", d->st_nlink);
# if LEAKY_STDLIB_ENABLE
	ft_printf("%s\t%s\t", passbuf->pw_name, groupbuf->gr_name);
# endif
	ft_printf("%5d ", d->st_size);

# if LEAKY_STDLIB_ENABLE
	ft_printf("%s ", timebuf);
	ft_strdel(&timebuf);
# endif
	ft_printf("%s\n", d->name);

	e->print_initiated = 1;
}

/*
 *	Bidouille rapide pour affichage en colonnes propre
 *	TODO: modifier l'ordre d'affichage ! Zigzag vertical, pas horizontal !
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
		while (++i < spaces && e->line_len < e->termwidth)
		{
			ft_putchar(' ');
			e->line_len++;
		}
	}
//	ft_printf("e->linelen = %d\n", e->line_len);
}
