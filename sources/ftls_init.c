/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 18:04:49 by amulin            #+#    #+#             */
/*   Updated: 2016/04/07 20:26:03 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ftls_init_env(t_env *e, char *progname)
{
	int	i;

	(void)progname;
//	if (!(e->progname = ft_strdup(progname)))
//		ftls_exit_on_error(e, NULL, errno);
	if (!(e->options = ft_strnew(10)))
		return (1);
	ft_bzero(e->options, 10);
	ft_bzero(e->supported_option, 7);
//	ft_strcpy(e->supported_options, "lRart");

	e->supported_option = (char**)malloc(sizeof(char*) * 10);
	i = 0;
	while (i < 10)
	{
		e->supported_option[i] = ft_strnew(2);
		ft_bzero(e->supported_option[i], 2);
	}
	e->supported_option[0][0] = 'l';
	e->supported_option[1][0] = 'R';
	e->supported_option[2][0] = 'a';
	e->supported_option[3][0] = 'r';
	e->supported_option[4][0] = 't';
	e->args_nomore = 0;
	return (0);
}

int	ftls_free_all(t_env *e)
{
	ft_strdel(&(e->options));
	return (0);
}
