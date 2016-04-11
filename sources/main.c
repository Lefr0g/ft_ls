/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 11:37:15 by amulin            #+#    #+#             */
/*   Updated: 2016/04/11 16:59:09 by amulin           ###   ########.fr       */
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

int		main(int ac, char **av)
{
	t_env	e;
	char	c;
//	char	**parsed_opt;

	int		i;

	if (ftls_init_env(&e, av[0]))
		return (1);

	if (ac == 1)
	{
		ft_putstr("Case 1: no argument (not implemented)\n");
	}
	else
	{
		if ((c = ft_parse_options(av, e.supported_option, &(e.cli_option))))
		{
			ftls_print_error_illegal_option(av[0], c);
			ftls_print_usage_stderr(&e);
		}
		i = -1;
		while (e.cli_option[++i])
		{
			ft_printf("Option %d = %s\n", i, e.cli_option[i]);
		}

	}
	ftls_free_all(&e);
	return (0);
}
