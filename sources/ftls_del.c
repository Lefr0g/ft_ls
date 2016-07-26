/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 18:42:37 by amulin            #+#    #+#             */
/*   Updated: 2016/07/26 18:44:22 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ftls_free_all(t_env *e)
{
	int	i;

	i = -1;
	ft_strdel(&(e->progname));
	while (++i < OPT_ARRAY_SIZE)
		ft_strdel(&(e->supported_option[i]));
	ft_strarray_del(&(e->cli_option));
	ft_strarray_del(&(e->cli_notopt));
	if (e->lst)
		ft_lstdel(&(e->lst), &ftls_elemdel);
	return (0);
}

/*
** This function is designed for use as a parameter for ft_lstdel()
*/

void	ftls_elemdel(void *ptr, size_t size)
{
	t_entry	*d;

	d = (t_entry*)ptr;
	if (d->name)
		ftls_strdelnfree(d->name);
	if (d->prefix)
		ftls_strdelnfree(d->prefix);
	if (d->linktarget)
		ftls_strdelnfree(d->linktarget);
	if (d->pw_name)
		ft_strdel(d->pw_name);
	if (d->gr_name)
		ft_strdel(d->gr_name);
	ft_memdel((void**)&(d->pw_name));
	if (d->size_str)
		ftls_strdelnfree(d->size_str);
	ft_bzero(ptr, size);
	ft_memdel(&ptr);
}

/*
**	Ad-hoc function for char** deletion and free, for norme compliance
*/

void	ftls_strdelnfree(char **str)
{
	ft_strdel(str);
	ft_memdel((void**)&(str));
}
