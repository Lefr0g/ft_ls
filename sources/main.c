/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 11:37:15 by amulin            #+#    #+#             */
/*   Updated: 2016/04/14 19:56:16 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
 *
 *	Flow
 *	- Initialiser env
 *	- Parser les args de la fonction
 *		- Verifier que chaque option est valide (via libft)
 *		- Recuperer la liste des options
 *		- Recupere la liste des non-options
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

	int		i;

	(void)ac;

	if (ftls_init_env(&e, ac, av))
		return (1);

	i = -1;
	while (e.cli_notopt[++i])
	{
		if (!opendir(e.cli_notopt[i]))
			ft_print_error(av[0], e.cli_notopt[i], errno);
		else
			ft_printf("%s is a directory\n", e.cli_notopt[i]);
	}

	i = -1;
	while (++i < ac)
		ft_printf("arg %d = %s\n", i, av[i]);



	ft_putstr("\nPrinting sorted program arguments:\n");
	ft_putstr(">>> Options:\n");
	i = -1;
	while (e.cli_option[++i])
	{
		ft_printf("\tOption %d = %s\n", i, e.cli_option[i]);
	}
	ft_putstr(">>> Files, directories or bad arguments:\n");
	i = -1;
	while (e.cli_notopt[++i])
	{
		ft_printf("\tNon-option %d = %s\n", i, e.cli_notopt[i]);
	}
	ftls_free_all(&e);
	return (0);
}
