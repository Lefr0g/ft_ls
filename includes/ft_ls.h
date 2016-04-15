/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 10:52:12 by amulin            #+#    #+#             */
/*   Updated: 2016/04/14 19:27:11 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "libft_extra.h"
# include <dirent.h>

# include <sys/stat.h>

# define OPT_ARRAY_SIZE 7

typedef struct	s_details
{
	int				isdir;
	char			*path;
	struct dirent	*drnt;
	struct stat		*stt;
	t_list			*subdir;
}				t_details;

typedef struct	s_env
{
	t_list			*rep;
	char			*progname;
	char			*supported_option[OPT_ARRAY_SIZE];
	char			**cli_option;
	char			**cli_notopt;
}				t_env;

/*
** ftls_init.c
*/
int				ftls_parse_cli_args(t_env *e, int ac, char **av);
int				ftls_init_env(t_env *e, int ac, char **av);
int				ftls_init_details(t_details *d);
int				ftls_free_all(t_env *e);

/*
** main.c
*/
//void			ftls_exit_on_error(t_env *e, char *arg, int errnum);

/*
** ftls_misc.c
*/
void			ftls_decode_type(mode_t st_mode, char *out);
void			ftls_decode_access_rights(mode_t st_mode, char *out);
void			ftls_decode_mode(mode_t st_mode);

/*
** ftls_error.c
*/
void			ftls_print_usage_stderr(t_env *e);
void			ftls_print_error_illegal_option(char *progname, char option);

#endif
