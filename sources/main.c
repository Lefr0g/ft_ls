/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 11:37:15 by amulin            #+#    #+#             */
/*   Updated: 2016/04/08 18:03:48 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
 *
 *	Flow
 *	- Initialiser env
 *	- Parser les args de la fonction
 *		- Verifier que chaque option est valide (via libft)
 *		- Lever les flags correspondant a chaque option (spec)
 *
 *
 *
 *
 *
 *
 *
*/

void	ftls_print_usage_stderr(t_env *e)
{
	int	i;

	ft_putstr_fd("usage: ", 2);
	ft_putstr_fd(e->progname, 2);
	ft_putstr_fd(" [-", 2);
	i = -1;
	while (e->supported_option[++i][0])
		ft_putchar_fd(e->supported_option[i][0], 2);
//	ft_putstr_fd(e->supported_options, 2);
	ft_putstr_fd("] [file ...]\n", 2);
}

void	ftls_print_error_illegal_option(char *progname, char option)
{
	ft_putstr_fd(progname, 2);
	ft_putstr_fd(": illegal option -- ", 2);
	ft_putchar_fd(option, 2);
	ft_putstr_fd("\n", 2);
}

int		main(int argc, char **argv)
{
	t_env	e;
	char	c;
	char	**parsed_opt;

	int		i;

	if (ftls_init_env(&e, argv[0]))
		return (1);

	if (argc == 1)
	{
		ft_putstr("Case 1: no argument (not implemented)\n");
	}
	else
	{
		if ((c = ft_parse_options(argv, e.supported_option,
						&parsed_opt)))
		{
			ftls_print_error_illegal_option(argv[0], c);
			ftls_print_usage_stderr(&e);
		}
		i = -1;
		while (parsed_opt[++i])
		{
			ft_printf("Option %d = %s\n", i, parsed_opt[i]);
		}

	}
	ftls_free_all(&e);
	return (0);
}
