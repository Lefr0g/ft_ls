/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 10:52:12 by amulin            #+#    #+#             */
/*   Updated: 2016/04/07 20:21:42 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"

# include <errno.h>

typedef struct	s_details
{
	char			*path;
	struct dirent	*s_dirent;
	struct stat		*s_stat;
	t_list			*subdir;
}				t_details;

typedef struct	s_env
{
	char			*progname;
	char			*options;
	char			supported_options[7];
	int				args_nomore;
}				t_env;

/*
** ftls_init.c
*/
int				ftls_init_env(t_env *e, char *progname);
int				ftls_free_all(t_env *e);

/*
** main.c
*/
void			ftls_parse_args(int ac, char **av, char **valid);
void			ftls_exit_on_error(t_env *e, char *arg, int errnum);
void			ftls_print_usage_stderr(t_env *e);
void			ftls_check_illegal_options(char **valid, char **tested, int qtity);

#endif
