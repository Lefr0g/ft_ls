/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 11:37:15 by amulin            #+#    #+#             */
/*   Updated: 2016/08/25 18:09:10 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ftls_isdir(char *path, char *progname, int verbose)
{
	int	ret;
	DIR	*dirstream;

	dirstream = NULL;
	if (!(dirstream = opendir(path)))
	{
		if (!(ret = 0) && verbose)
			ft_print_error(progname, path, errno);
	}
	else
		ret = 1;
	if (dirstream && closedir(dirstream) && verbose)
		ft_print_error(progname, path, errno);
	return (ret);
}

int		ftls_isfile(char *path, char *progname, int verbose)
{
	int			ret;
	struct stat	statbuf;

	if (lstat(path, &statbuf))
	{
		if (!(ret = 0) && verbose)
			ft_print_error(progname, path, errno);
	}
	else
		ret = 1;
	return (ret);
}

int		main(int ac, char **av)
{
	t_env	e;

	if (ftls_init_env(&e, av) || FTLS_PARSE_CLI_ARGS(&e, ac, av))
		return (1);
	ftls_init_options(&e);
	if (!e.iscli)
	{
		ftls_process_entry(&e, ".", NULL);
	}
	else
	{
		ftls_process_argnames(&e);
	}
	ftls_free_all(&e);
	return (0);
}
