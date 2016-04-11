/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 16:32:55 by amulin            #+#    #+#             */
/*   Updated: 2016/04/11 16:34:44 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_ls.h"

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
