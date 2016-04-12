/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 11:37:15 by amulin            #+#    #+#             */
/*   Updated: 2016/04/12 19:33:59 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


/*
** Return a string array containing all cli arguments that can't be found in
** the 'cli_options' string array.
**
**	WORK IN PROGRESS
*/

char	**ftls_parse_notopts(int ac, char **av, char **cli_option)
{
	char	**out;
	int		i;
	int		j;

	i = 0;
	while (cli_option[i])
		i++;
	out = (char**)ft_memalloc(sizeof(char*) * (ac - i + 1));
	j = -1;
	i = 0;
	while (i < ac)
	{
		if (!ft_find_double_str(av[i], cli_option))
			out[++j] = ft_strdup(av[i]);
		i++;
	}
	out[++j] = NULL;
	return (out);
}

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
	char	c;

	int		i;

	(void)ac;

	if (ftls_init_env(&e, av[0]))
		return (1);


	if ((c = ft_parse_options(av, e.supported_option, &(e.cli_option))))
	{
		ftls_print_error_illegal_option(av[0], c);
		ftls_print_usage_stderr(&e);
	}
		e.cli_notopt = ftls_parse_notopts(ac, av, e.cli_option);
	i = 0;
	while (av[++i])
		if (!opendir(av[i]) && av[i][0] != '-')
			ft_print_error(av[0], av[i], errno);

	ft_putstr("Printing sorted program arguments:\n");
	ft_putstr(">>> Options:\n");
	i = -1;
	while (e.cli_option[++i])
	{
		ft_printf("Option %d = %s\n", i, e.cli_option[i]);
	}
	ft_putstr("\n>>> Files, directories or bad arguments:\n");
	i = -1;
	while (e.cli_notopt[++i])
	{
		ft_printf("Non-option %d = %s\n", i, e.cli_notopt[i]);
	}
	ftls_free_all(&e);
	return (0);
}
