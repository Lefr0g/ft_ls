/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 11:37:15 by amulin            #+#    #+#             */
/*   Updated: 2016/04/07 20:27:41 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ftls_print_usage_stderr(t_env *e)
{
	ft_putstr_fd("usage: ", 2);
	ft_putstr_fd(e->progname, 2);
	ft_putstr_fd(" [-", 2);
	ft_putstr_fd(e->supported_options, 2);
	ft_putstr_fd("] [file ...]\n", 2);
}

/*
** 'valid' contains all accepted options. The last element is filled with '\0'
*/
/*
void	ft_check_illegal_options(int ac, char **av, char **valid)
{
}
*/

void	ftls_parse_args(int argc, char **argv, char **valid)
{
	(void)argc;
	(void)argv;
	(void)valid;
}

int		main(int argc, char **argv)
{
	t_env	e;

	(void)argc;
	(void)argv;

	ftls_init_env(&e, argv[0]);
	ft_putstr("CHECK\n");
//	if (argc > 1)
//		ftls_parse_args(argc, argv,);
	ftls_free_all(&e);
	return (0);
}
