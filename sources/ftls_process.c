/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 19:00:27 by amulin            #+#    #+#             */
/*   Updated: 2016/06/10 20:33:13 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	This is the standard processing function.
**	Algo:
**		- Creation du path + gestion affichage premiere ligne si besoin
**		- Copie data dans nouvelle liste subdir
**		- Tri liste subdir
**		- Affichage subdir
**		- Si option -R, lancement recursivite
**		- Free liste subdir
*/

int		ftls_process_entry(t_env *e, char *name, char *prefix)
{
	t_list		*subdir;
	t_entry		*entptr;
	char		*path;

	path = ftls_process_path(e, name, prefix);
	e->totalblocks = 0;
	subdir = ftls_get_subdir(e, path);
	ft_strdel(&path);
	if (!subdir)
		return (1);
	entptr = subdir->content;
	if (!e->sort_none)
	{
		ft_lstsort(&subdir, (void*)&(entptr->name) - (void*)entptr,
				&ftls_compare_str);
		ft_lstsort(&e->lst, (void*)&entptr->st_mode_ptr - (void*)entptr,
				&ftls_compare_type);
	}
	if (e->showlist && e->atleastonetoshow)
		ft_printf("total %d\n", e->totalblocks);
	e->atleastonetoshow = 0;
	ftls_print_dir(e, subdir);
	if (e->recursive)
		ftls_recursion(e, subdir);
	ft_lstdel(&(subdir), &ftls_elemdel);
	return (0);
}

/*
**	This function is only used to create the first list when 'names' are given
**	as aguments
*/

int		ftls_process_argnames(t_env *e)
{
	t_list	*ptr;
	int		i;
	t_entry	*entptr;

	i = -1;
	while (e->cli_notopt[++i])
		if (e->cli_notopt[i][0])
			ftls_add_entry(&e->lst, e, e->cli_notopt[i], NULL);
	if (!e->lst)
		return (0);
	entptr = e->lst->content;
	if (!e->sort_none)
	{
		ft_lstsort(&e->lst, (void*)&entptr->name - (void*)entptr,
				&ftls_compare_str);
		ft_lstsort(&e->lst, (void*)&entptr->st_mode_ptr - (void*)entptr,
				&ftls_compare_type);
	}
	ptr = e->lst;
	while (ptr)
	{
		entptr = ptr->content;
//		ftls_debug_show_entry(entptr);
		if (ftls_is_entry_treatable(e, entptr))
			ftls_process_entry(e, *(entptr->name), NULL);
		else
			ftls_print_entry(e, entptr);
		ptr = ptr->next;
	}
//	ftls_manage_spacing(e);
	return (0);
}

/*
**	Returns a new list of all the entries contained in 'path'
**	Also generates some metadata used for column layout (default output)
*/

t_list	*ftls_get_subdir(t_env *e, char *path)
{
	t_list			*subdir;
	DIR				*dir;
	struct dirent	*my_dirent;

	subdir = NULL;
	if (!(dir = opendir(path)))
		return (NULL);
	e->col_len = 0;
	while ((my_dirent = readdir(dir)))
	{
		ftls_add_entry(&subdir, e, my_dirent->d_name, path);
	}
	if (closedir(dir))
		return (NULL);
	return (subdir);
}

/*
**	Triggers recursive behavior
*/

void	ftls_recursion(t_env *e, t_list *subdir)
{
	t_list	*ptr;
	t_entry	*entptr;

	ptr = subdir;
	while (ptr)
	{
		entptr = ptr->content;
		if (ftls_is_entry_treatable(e, entptr)
				&& ftls_is_entry_showable(e, entptr))
			ftls_process_entry(e, *(entptr->name), *(entptr->prefix));
		ptr = ptr->next;
	}
}
