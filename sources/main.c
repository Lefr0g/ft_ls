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

/*
 * Subfunction for ft_parse_options, designed to avoid doubles in the
 * 'stored' string table.
 * If found, the function returns a pointer to the double in the haystack
*/

char	*ft_find_double_str(char *needle, char **haystack)
{
	int	i;

	i = -1;
	while (haystack[++i])
		if (!ft_strcmp(needle, haystack[i]))
			return (haystack[i]);
	return (NULL);
}

/*
 * Subfunction for ft_parse_options, dedicated to testing the validity of
 * the 'tested' argument as an option, then duplicating if (if valid) into the
 * program's 'stored' table.
 * If the 'tested' argument is not a valid option, the function returns 1
*/

static int	get_options(int *i, char **valid, char *tested, char **stored)
{
	int	j;
	int	match;

	j = -1;
	match = 0;
	while (valid[++j][0])
		if (!ft_strcmp(valid[j], tested) && (match = 1)
				&& !ft_find_double_str(tested, stored))
		{
			stored[*i] = ft_strdup(tested);
			(*i)++;
		}
	if (!match)
		return (1);
	return (0);
}

/*
 * Subfunction for ft_parse_options that allocates sufficient memory to store
 * all valid options into a string array.
 * Notice that it will probably allocate more memory than necessary.
*/
static int	allocate_storage(char **tested, char ***stored)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tested[++i])
	{
		if (tested[i][0] == '-')
		{
			if (tested[i][1] == '-')
				j++;
			else
				j += ft_strlen(tested[i]);
		}
	}
	*stored = (char**)ft_memalloc(sizeof(char*) * (j + 1));
	if (!(*stored))
		return (1);
	return (0);
}

/*
 * This function ensures options given as program arguments are supported,
 * and retrieves supported options from the command line argument list.
 *
 * 'tested' is supposed to be main's argv, but it can be any string table
 * ending with a NULL pointer. However the first string of the array won't be
 * inspected.
 * 'valid' is the string table of supported options, it must be terminated by
 * an empty string.
 * 'checked' is a pointer to an unallocated string table that will store the
 * options validated by the function.
 *
 * The function ignores 'tested' stings unless they begin with a '-'
 * Characters following a '-' are treated individually
 * Characters following a '--' are treated as a single string
 * Upon reading '--\0' the function stops.
 *
 * For norme compliance, the flag indicating a '--\0' encounter was replaced by
 * setting k to a negative value.
 * 
 * The function returns '\0' when all options are valid, '-' if a long option
 * is invalid, or the char corresponding to an invalid short option.
 *
 * Note: this function is a quick substitute to an upcoming (TODO)
 * reimplementation of the cleaner getopt() and getopt_long() functions.
*/

char	ft_parse_options(char **tested, char **valid, char ***stored)
{
	int		i;
	int		j;
	int		k;
	char	buf[2];

	k = 0;
	if (!(i = 0) && allocate_storage(tested, stored))
		return ('!');
	ft_bzero(buf, 2);
	while (tested[++i] && (k = (tested[i][0] == '-' ? k : -1)) >= 0)
	{
		j = 0;
		if (tested[i][0] && tested[i][1] == '-'
				&& ((k = !tested[i][2] ? -1 : k) >= 0 || 1))
		{
			if (get_options(&k, valid, &tested[i][2], *stored) && k >= 0)
				return ('-');
		}
		else if (tested[i][1])
			while (tested[i][++j] && (buf[0] = tested[i][j]))
				if (get_options(&k, valid, buf, *stored))
					return (buf[0]);
	}
	return (0);
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
