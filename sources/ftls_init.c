/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 18:04:49 by amulin            #+#    #+#             */
/*   Updated: 2016/06/21 14:31:19 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ftls_parse_cli_args(t_env *e, int ac, char **av)
{
	int		i;
	int		j;
	char	c;
	char	**buf;

	if (!(buf = ft_strarray_dup(av)))
		return (1);
	if ((c = ft_parse_options(buf, e->supported_option, &(e->cli_option))))
		return (ftls_print_error_illegal_option(e, av[0], c));
	if (!(e->cli_notopt = (char**)ft_memalloc(sizeof(char*) * (ac + 1))))
		return (1);
	i = 0;
	j = -1;
	while (++i < ac)
		if (buf[i][0])
		{
			if (ft_isfile(buf[i], e->progname, 1))
				e->cli_notopt[++j] = ft_strdup(buf[i]);
			else
				e->cli_notopt[++j] = ft_strdup("");
		}
	ft_strarray_del(&buf);
	return (0);
}

int	ftls_init_env(t_env *e, char **av)
{
	int		i;

	ft_bzero(e, sizeof(*e));
	e->sort_time_val = 't';
	if (!(e->progname = ft_strdup(av[0])))
	{
		ft_print_error(av[0], NULL, errno);
		return (1);
	}
	i = -1;
	while (++i < OPT_ARRAY_SIZE)
		e->supported_option[i] = ft_strnew(2);
	e->supported_option[0][0] = 'A'; // Done
	e->supported_option[1][0] = 'L'; // Done
	e->supported_option[2][0] = 'R'; // Done
	e->supported_option[3][0] = 'S'; // Done
	e->supported_option[4][0] = 'a'; // Done
	e->supported_option[5][0] = 'c'; // Done
	e->supported_option[6][0] = 'f'; // Done
	e->supported_option[7][0] = 'h'; // TODO
	e->supported_option[8][0] = 'i'; // Almost done (TODO fix layout)
	e->supported_option[9][0] = 'n'; // Done
	e->supported_option[10][0] = 'r'; // Done
	e->supported_option[11][0] = 't'; // Done
	e->supported_option[12][0] = 'u'; // WIP
	e->supported_option[13][0] = 'l'; // Almost done (TODO fix layout)
	e->supported_option[14][0] = '1'; // Done
	e->termwidth = ftls_get_terminal_width(e);
	return (0);
}

int	ftls_init_entry(t_entry *ptr)
{
	ft_bzero(ptr, sizeof(t_entry));
	return (0);
}

int	ftls_init_options(t_env *e)
{
	int		i;
	char	c;

	i = -1;
	while (e->cli_option[++i] && (c = e->cli_option[i][0]))
	{
		e->show_all_nodot = (c == 'A') ? 1 : e->show_all_nodot;
		e->recursive = (c == 'R') ? 1 : e->recursive;
		e->sort_size = (c == 'S') ? 1 : e->sort_size;
		e->show_all = (c == 'a') ? 1 : e->show_all;
		e->show_num_id = (c == 'n') ? 1 : e->show_num_id;
		e->sort_none = (c == 'f') ? 1 : e->sort_none;
		e->human = (c == 'h') ? 1 : e->human;
		e->showinode = (c == 'i') ? 1 : e->showinode;
		e->reverse = (c == 'r') ? 1 : e->reverse;
		// Remplacer les flags de tri temporelles par une variable d'activation
		// et une variable de critere de tri (valeur ascii de l'option) afin que
		// seul le dernier critere de tri soit actif
		e->sort_timeacc = (c == 'u') ? 1 : e->sort_timeacc;
		e->sort_timemod = (c == 't') ? 1 : e->sort_timemod;
		e->sort_timech = (c == 'c') ? 1 : e->sort_timech;

		e->sort_time_val = (e->sort_timemod && (c == 'c' || c == 'u'))
			? c : e->sort_time_val;

		e->showlist = (c == 'l') ? 1 : e->showlist;
		e->followlink_sub = (c == 'L') ? 1 : e->followlink_sub;
		e->oneperline = (c == '1') ? 1 : e->oneperline;
	}
	if (e->show_num_id)
		e->showlist = 1;
	if (e->sort_none)
		e->show_all = 1;
	if (!e->sort_timemod && !e->show_all)
	{
		e->sort_timeacc = 0;
		e->sort_timech = 0;
	}
	if (e->sort_timeacc || e->sort_timech)
		e->sort_timemod = 0;
	e->followlink_cli = 1;
	if (e->showlist && !e->followlink_sub)
		e->followlink_cli = 0;
	return (0);
}

int	ftls_free_all(t_env *e)
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
