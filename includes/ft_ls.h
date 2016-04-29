/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 10:52:12 by amulin            #+#    #+#             */
/*   Updated: 2016/04/19 18:48:18 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "libft_extra.h"
# include <dirent.h>

# include <sys/stat.h>

# define OPT_ARRAY_SIZE 11

/*
 * Cette structure, 1 par dir entry, contient toutes les datas utiles au tri
 * et a l'affichage, ainsi que les addresses des entrees contigues et des
 * sous-repertoires.
 * TODO: Adapter pour pouvoir utiliser avec les fonctions de gestion de liste de
 * la libft.
*/
typedef struct	s_de
{
	// Below are copies from dirent
	ino_t					d_ino; // copy from dirent
	__uint8_t				d_namelen; // copy from dirent
	char d_name[255 + 1]	*d_name; // directory entry name, copy from dirent
	// Below are copies from struct stat
	mode_t					st_mode;
	nlink_t					st_nlinks;
	uid_t					st_uid;
	gid_t					st_gid;
	struct timespec			st_atimespec; // last access
	struct timespec			st_mtimespec; // last modification
	struct timespec			st_ctimespec; // last status change
	off_t					st_size; // in bytes
	// Below are custom variables
	char					*prefix; // used to obtain file path
	struct s_de				*next; // points to next dir entry at this level
	struct s_de				*subdir; // only if this entry is a dir
}				t_de;

/*
typedef struct	s_details
{
	int				isdir;
	DIR				*dirstream; // directory stream
	char			*name; // name of the directory
	char			*path; // full path of the directory
	struct dirent	*drnt;
//	struct stat		*stt;
	char			*ent_prefix; // to be added to 'names' to obtain entries paths
	char			**ent_names; // names of the entries contained in DIR
	int				ent_qtity; // number of entries in DIR
	int				ent_longest_name; // lenght, used for column output
	t_list			*subdir;
}				t_details;
*/

typedef struct	s_env
{
	t_list			*rep;
	char			*progname;
	char			*supported_option[OPT_ARRAY_SIZE];
	char			**cli_option;
	char			**cli_notopt;

	//				Option flags:
	char			showhidden; // starting with ., except . and .. (for -A)
	char			showspecial; // . and .. (for -a)
	char			recursive; // (for -R)
	char			reverse; // (for -r)
	char			sort_none; // (for -f)
	char			sort_size; // (for -S)
	char			sort_time_mod; // (for -t)
	char			human; // (for -h)
	char			color; // (for -G) (pas sur, semble trop time-consuming)
	char			showinode; // (for -i)
	char			showlist; // (for -l)
	char			oneperline; // (for -1)
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
