/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 18:04:49 by amulin            #+#    #+#             */
/*   Updated: 2016/05/23 19:08:27 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ftls_parse_cli_args(t_env *e, int ac, char **av)
{
	int		i;
	int		j;
	char	c;
	char	**buf;

	if (!(buf = ft_strarray_dup(av)))
		return (1);

	if ((c = ft_parse_options(buf, e->supported_option, &(e->cli_option))))
	{
		ftls_print_error_illegal_option(av[0], c);
		ftls_print_usage_stderr(e);
		return (1);
	}
	if (!(e->cli_notopt = (char**)ft_memalloc(sizeof(char*) * (ac + 1))))
		return (1);
	i = 0;
	j = -1;
	while (++i < ac)
		if (buf[i][0] && ft_isfile(buf[i], e->progname, 1))
			if (!(e->cli_notopt[++j] = ft_strdup(buf[i])))
				return (1);
	ft_strarray_del(&buf);
	return (0);
}

int	ftls_init_env(t_env *e, char **av)
{
	int		i;

	ft_bzero(e, sizeof(*e));
	if (!(e->progname = ft_strdup(av[0])))
	{
		ft_print_error(av[0], NULL, errno);
		return (1);
	}
	i = -1;
	while (++i < OPT_ARRAY_SIZE)
		e->supported_option[i] = ft_strnew(2);
	e->supported_option[0][0] = 'A';
	e->supported_option[1][0] = 'R';
	e->supported_option[2][0] = 'S';
	e->supported_option[3][0] = 'a';
	e->supported_option[4][0] = 'f';
	e->supported_option[5][0] = 'h';
	e->supported_option[6][0] = 'i';
	e->supported_option[7][0] = 'r';
	e->supported_option[8][0] = 't';
	e->supported_option[9][0] = 'l';
//	ft_strcpy(e->supported_option[5], "long");
//	e->supported_option[x][0] = 'G';
	
	return (0);
}

int	ftls_init_details(t_de *d)
{
//	d->isdir = 0;
//	d->path = NULL;
//	d->drnt = NULL;
//	d->stt = NULL;
	d->prefix = NULL;
	d->subdir = NULL;
	return (0);
}

int	ftls_init_options(t_env *e)
{
	int		i;
	char	c;

	i = -1;
	while (e->cli_option[++i] && (c = e->cli_option[i][0]))
	{
		e->showhidden = (c == 'A') ? 1 : e->showhidden;
		e->recursive = (c == 'R') ? 1 : e->recursive;
		e->sort_size = (c == 'S') ? 1 : e->sort_size;
		e->showspecial = (c == 'a') ? 1 : e->showspecial;
		e->sort_none = (c == 'f') ? 1 : e->sort_none;
		e->human = (c == 'h') ? 1 : e->human;
		e->showinode = (c == 'i') ? 1 : e->showinode;
		e->reverse = (c == 'r') ? 1 : e->reverse;
		e->sort_time_mod = (c == 't') ? 1 : e->sort_time_mod;
		e->showlist = (c == 'l') ? 1 : e->showlist;
	}
	return (0);
}

int	ftls_free_all(t_env *e)
{
	int	i;

	i = -1;
	ft_strdel(&(e->progname));
	while (++i < OPT_ARRAY_SIZE)
		ft_strdel(&(e->supported_option[i]));
//	ft_printf("Deleting e->cli_option\n");
	ft_strarray_del(&(e->cli_option));
//	ft_printf("Deleting e->cli_notopt\n");
	ft_strarray_del(&(e->cli_notopt));

	ft_lstdel(&(e->lst), &test_elemdel);

	ft_printf("ftls_free_all completed\n");


	return (0);
}
