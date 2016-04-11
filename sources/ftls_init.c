/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 18:04:49 by amulin            #+#    #+#             */
/*   Updated: 2016/04/11 17:12:32 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ftls_init_env(t_env *e, char *progname)
{
	int	i;

	(void)progname;
	if (!(e->progname = ft_strdup(progname)))
	{
		ft_print_error(progname, NULL, errno);
		exit(1);
	}
	i = -1;
	while (++i < OPT_ARRAY_SIZE)
		e->supported_option[i] = ft_strnew(2);
	e->supported_option[0][0] = 'l';
	e->supported_option[1][0] = 'R';
	e->supported_option[2][0] = 'a';
	e->supported_option[3][0] = 'r';
	e->supported_option[4][0] = 't';
	ft_strcpy(e->supported_option[5], "long");

	return (0);
}

int	ftls_free_all(t_env *e)
{
	int	i;

	i = -1;
	while (e->cli_option[++i])
		ft_strdel(&(e->cli_option[i]));
	ft_memdel((void**)&(e->cli_option));
	i = -1;
	while (++i < OPT_ARRAY_SIZE)
		ft_strdel(&(e->supported_option[i]));


	return (0);
}
