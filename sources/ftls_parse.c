/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 16:19:20 by amulin            #+#    #+#             */
/*   Updated: 2016/08/24 16:19:57 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ftls_parse_cli_args_linux(t_env *e, int ac, char **av)
{
	int		i;
	int		j;
	char	c;
	char	**buf;

	if (!(buf = ft_strarray_dup(av)))
		return (1);
	if ((c = ft_parse_options_keep_doubles(buf, e->supported_option,
					&(e->cli_option))))
		return (ftls_print_error_illegal_option(e, av[0], c));
	if (!(e->cli_notopt = (char**)ft_memalloc(sizeof(char*) * (ac + 1))))
		return (1);
	i = 0;
	j = -1;
	while (++i < ac)
	{
		if ((buf[i][0] || (!buf[i][0] && !av[i][0]))
				&& (e->iscli = 1) && ftls_isfile(buf[i], e->progname, 1))
			e->cli_notopt[++j] = ft_strdup(buf[i]);
		else if (!ft_strlen(buf[i]) && !ft_strlen(av[i]))
			e->cli_notopt[++j] = ft_strdup("");
	}
	ft_strarray_del(&buf);
	return (0);
}

int		ftls_parse_cli_args_osx(t_env *e, int ac, char **av)
{
	int		i;
	int		j;
	char	c;
	char	**buf;

	if (!(buf = ft_strarray_dup(av)))
		return (1);
	if ((c = ft_parse_options_keep_doubles(buf, e->supported_option,
					&(e->cli_option))))
		return (ftls_print_error_illegal_option(e, av[0], c));
	if (!(e->cli_notopt = (char**)ft_memalloc(sizeof(char*) * (ac + 1))))
		return (1);
	i = 0;
	j = -1;
	while (++i < ac)
	{
		if (buf[i][0] && (e->iscli = 1) && ftls_isfile(buf[i], e->progname, 1))
			e->cli_notopt[++j] = ft_strdup(buf[i]);
		else if (!ft_strlen(buf[i]) && !ft_strlen(av[i]))
			exit(ft_printf("%s: fts_open: No such file or directory\n", av[0]));
	}
	ft_strarray_del(&buf);
	return (0);
}
