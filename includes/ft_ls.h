/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 10:52:12 by amulin            #+#    #+#             */
/*   Updated: 2016/05/24 20:09:43 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "libft_extra.h"
# include <dirent.h>

# ifdef __APPLE__
#  define TIME_TYPE struct timespec
#  define ATIME	st_atimespec
#  define MTIME	st_mtimespec
#  define CTIME	st_atimespec
# elif __linux__
#  define TIME_TYPE time_t
#  define ATIME	st_atime
#  define MTIME	st_mtime
#  define CTIME	st_atime
# endif


# include <sys/stat.h>

# include <sys/xattr.h>
# include <sys/acl.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

// Optional ?
# include <sys/types.h>
# include <uuid/uuid.h>

# define OPT_ARRAY_SIZE 12

// Disable the following for a clean Valgrind report
# define LEAKY_STDLIB_ENABLE 1

/*
 * Cette structure, 1 par dir entry, contient toutes les datas utiles au tri
 * et a l'affichage.
 * Si l'entree est un repertoire a afficher OU l'option -R a ete donnee,
 * 'subdir' pointe vers une liste nouvelle liste contenant les entrees de
 * ce sous-repertoire.
 * Sinon, 'subdir' est NULL.
 * Le parcours des entrees contenues dans un repertoire se fait a l'aide
 * des pointeurs next ou prev de la t_list contenant cette structure.
*/
typedef struct	s_de
{
	// Below values should match return from dirent
	ino_t					d_ino;
	__uint8_t				d_namelen;
	char					d_name[255 + 1];
	// Below are copies from struct stat
	mode_t					st_mode;
	nlink_t					st_nlink;
	uid_t					st_uid;
	gid_t					st_gid;
	TIME_TYPE				st_atimespec; // last access
	TIME_TYPE				st_mtimespec; // last modification
	TIME_TYPE				st_ctimespec; // last status change
	off_t					st_size; // in bytes
	// Below are custom variables
	char					*prefix; // used to obtain file path
	t_list					*subdir; // only if this entry is a dir
	t_list					*parent; // only if this entry is a subdir
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
	t_list			*lst;
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
//	char			color; // (for -G) (pas sur, semble trop time-consuming)
	char			showinode; // (for -i)
	char			showlist; // (for -l)
	char			oneperline; // (for -1)
}				t_env;

/*
** ftls_init.c
*/
int				ftls_parse_cli_args(t_env *e, int ac, char **av);
int				ftls_init_env(t_env *e, char **av);
int				ftls_init_details(t_de *d);
int				ftls_init_options(t_env *e);
int				ftls_free_all(t_env *e);

/*
** main.c
*/
//void			ftls_exit_on_error(t_env *e, char *arg, int errnum);
int				ft_isdir(char *path, char *progname, int verbose);
int				ft_isfile(char *path, char *progname, int verbose);


/*
** ftls_list.c
*/
int				ftls_add_entry(t_list **alst, t_env *e, char *name,
		char *prefix);
void			ftls_copy_details(t_de *dst, struct stat *src, char *name,
		char *prefix);
int				ftls_manage_subdir(t_list *current, t_list **subdir, t_env *e);
void			ftls_elemdel(void *ptr, size_t size);

/*
** ftls_misc.c
*/
void			ftls_decode_type(mode_t st_mode, char *out);
void			ftls_decode_access_rights(mode_t st_mode, char *out);
void			ftls_decode_mode(mode_t st_mode);

/*
** flts_print.c
*/
void			ftls_quick_ll(t_env *e, t_de *d);

/*
** ftls_error.c
*/
void			ftls_print_usage_stderr(t_env *e);
void			ftls_print_error_illegal_option(char *progname, char option);

/*
** ftls_debug.c
*/
void			ftls_debug_show_args(t_env *e);
void			ftls_debug_show_list(t_list *lst);
void			ftls_debug_show_options(t_env *e);

#endif
