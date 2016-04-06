/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 11:37:15 by amulin            #+#    #+#             */
/*   Updated: 2016/04/06 19:12:32 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ftls_print_usage(t_env *e)
{
	ft_printf("usage: %s [-%s] [file ...]\n", e->progname,
			e->supported_options);
}

void	ftls_exit_on_error(t_env *e, char *arg, int errnum)
{
	if (!e->progname && !errnum)
	{
		ft_putstr("Fatal error: you accidentally the whole program.\n");
		ft_putstr("             Just stay away from computers. Please.\n");
	}
	else if (!e->progname)
		ft_printf("Fatal error: %s", strerror(errnum));
	else if (errnum)
		ft_printf("%s: %s: %s\n", e->progname, arg, strerror(errnum));
	else
	{
		ft_printf("%s: %s\n", e->progname, arg);
		ftls_print_usage(e);
	}
	exit(1);
}

void	ftls_parse_args(t_env *e, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (!strcmp(argv[i], "--"))
		{
			e->args_nomore = 1;
			ft_printf("Double dash at position %d\n", i);
		}
		else if (ft_strlen(argv[i]) > 2 && ft_strnstr(argv[i], "--", 2))
		{
			ftls_exit_on_error(e, "illegal option -- -", 0);
		}
//		printf("Errno = %d\n", errno);
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_env	e;

	ftls_init_env(&e, argv[0]);
	if (argc > 1)
		ftls_parse_args(&e, argc, argv);
	ftls_free_all(&e);
	return (0);
}
