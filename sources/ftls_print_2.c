/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_print_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 15:59:52 by amulin            #+#    #+#             */
/*   Updated: 2016/07/26 18:51:37 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
		ft_putendl(name);
	else
	{
		i = -1;
		if (e->line_len + (int)ft_strlen(name) < e->termwidth)
			e->line_len += ft_strlen(name);
		else
		{
			ft_putchar('\n');
			e->line_len = ft_strlen(name);
		}
		ft_putstr(name);
		spaces = e->col_len - ft_strlen(name) + 1;
		while (++i < spaces && e->line_len < e->termwidth)
		{
			ft_putchar(' ');
			e->line_len++;
		}
	}
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
		else if (!ptr->prev)
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
		FTLS_PRINT_LISTED(e, entptr);
	else
		ftls_print_name(e, *(entptr->name));
	e->print_initiated = 1;
}

void	ftls_manage_spacing(t_env *e)
{
	if (!e->oneperline && !e->showlist && e->print_initiated)
		ft_putchar('\n');
}
