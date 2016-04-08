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

/*
 * This functions checks that every strings given in 'tested' can also be found
 * in 'valid'.
 * If one of the strings cannot be found, the function returns 1. Otherwise
 * 0 is returned.
 * 'tested' and 'valid' must be terminated by an empty string !
*/

int		ft_tabtab_compare();

/*
 * This function ensures options given as program arguments are supported by
 * said program.
 * 'tested' is supposed to be main's argv, but it can be any string table
 * ending with an empty string.
 * 'valid' is the string table of supported options, it must be terminated by
 * an empty string.
 * The function ignores 'tested' stings unless they begin with a '-'
 * Characters following a '-' are treated individually
 * Characters following a '--' are considered as a long option
 * Upon reading '-- ' the function stops.
 * 
 * The function returns '\0' when all options are valid, '-' if a long option
 * is invalid, or the char corresponding to an invalid short option.
 *
 * Note: this function is a quick substitute to an upcoming (TODO)
 * reimplementation of the cleaner getopt() and getopt_long() functions.
*/

char	ft_check_arg_options(int ac, char **tested, char **valid)
{
	int		i;
	int		j;
	int		k;
	int		match;
	int		endopt;
	char	buf[2];

	(void)k;
	(void)valid;

	endopt = 0;
	ft_bzero(buf, 2);
	i = 0;
	while (++i < ac && ft_strlen(tested[i]) && !endopt)
	{
		if (tested[i][0] == '-')
		{
			if (tested[i][1] == '-')
			{
				if (!tested[i][2])
				{
					endopt = 1;
//					ft_printf("End of options found\n");
				}
//				else
//					ft_printf("%s is a long option\n", tested[i]);
			}
			else if (tested[i][1])
			{
//				ft_printf("%s contains at least one short option\n", tested[i]);
				k = 0;
				while (tested[i][++k])
				{
					j = 0;
					match = 0;
					while (valid[j][0])
					{
						buf[0] = tested[i][k];
						if (!ft_strcmp(valid[j], buf))
						{
							ft_printf("Match on %s !\n", buf);
							match = 1;
						}
						j++;
					}
					if (!match)
						return (tested[i][k]);
				}
			}
//			else
//				ft_putstr("Single dash found\n");
		}
//			ft_printf("i = %d, tested[%d] = %s, j = %d, valid[%d] = %s\n",
//					i, i, tested[i], j, j, valid[j]);

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
	char	c;

	if (ftls_init_env(&e, argv[0]))
		return (1);

	if (argc == 1)
	{
		ft_putstr("Case 1: no argument (not implemented)\n");
	}
	else
	{
//		ft_putstr("Case 2: arguments given\n");
		if ((c = ft_check_arg_options(argc, argv, e.supported_option)))
		{
			ftls_print_error_illegal_option(argv[0], c);
			ftls_print_usage_stderr(&e);
		}
	}
	ftls_free_all(&e);
	return (0);
}
