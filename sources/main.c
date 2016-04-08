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

/*
 *
 *	Flow
 *	- Initialiser env
 *	- Parser les args de la fonction
 *		- Verifier que chaque option est valide (via libft)
 *		- Lever les flags correspondant a chaque option
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
	ft_putstr_fd("usage: ", 2);
	ft_putstr_fd(e->progname, 2);
	ft_putstr_fd(" [-", 2);
//	ft_putstr_fd(e->supported_options, 2);
	ft_putstr_fd("] [file ...]\n", 2);
}

/*
** 'valid' contains all accepted options. The last element is filled with '\0'
*/

int		ft_check_arg_options(int ac, char **av, char **valid)
{
	int	i;
	int	j;
	int	match;

	i = 0;
	while (i < ac)
	{
		j = 0;
		match = 0;
		while (!match && valid[j])
		{
			if (ft_strstr(valid[j], av[i]))
				match = 1;
			j++;
		}
		if (!match)
			return (1);
		i++;
	}
	return (0);
}


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

	int		readret;
	char	*buf;

	buf = ft_strnew(11);
	ft_bzero(buf, 11);
	if (argc == 1)
	{
	}
	else
	{
	if (ftls_init_env(&e, argv[0]))
		return (1);
	ft_putstr("FT_PUTSTR\n");
	ft_printf("FT_PRINTF\n");
//	if (argc > 1)
//		ftls_parse_args(argc, argv,);
	ftls_free_all(&e);
	}
	return (0);
}
