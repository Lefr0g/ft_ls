/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 10:52:12 by amulin            #+#    #+#             */
/*   Updated: 2016/06/09 19:41:14 by amulin           ###   ########.fr       */
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

// Used to get terminal size
# include <sys/ioctl.h>

// Optional ?
# include <sys/types.h>
# include <uuid/uuid.h>

# define OPT_ARRAY_SIZE 12
# define LIST_MODE_COLUMNS 7

// Disable the following for a clean Valgrind report
# define LEAKY_STDLIB_ENABLE 1


/*
**	Nouvelle structure pour version optimisee.
**	Pas de parcours de liste en profondeur
*/
typedef struct	s_entry
{
	char					**name;
	char					**prefix;
	mode_t					st_mode;
	mode_t					st_mode_ptr[1];
	nlink_t					st_nlink;
	uid_t					st_uid;
	gid_t					st_gid;
	TIME_TYPE				st_atimespec; // last access
	TIME_TYPE				st_mtimespec; // last modification
	TIME_TYPE				st_ctimespec; // last status change
	off_t					st_size; // in bytes

}				t_entry;



typedef struct	s_env
{
	t_list			*lst;
	char			*progname;
	char			*supported_option[OPT_ARRAY_SIZE];
	char			**cli_option;
	char			**cli_notopt;

	//				Option flags:
	char			show_all_nodot; // starting with . except "." and .. (for -A)
	char			show_all; // All including "." and .. (for -a)
	char			recursive; // (for -R)
	char			reverse; // (for -r)
	char			sort_none; // (for -f)
	char			sort_size; // (for -S)
	char			sort_timemod; // (for -t)
	char			human; // (for -h)
//	char			color; // (for -G) (pas sur, semble trop time-consuming)
	char			showinode; // (for -i)
	char			showlist; // (for -l)
	char			oneperline; // (for -1)

	//				I/O data for human readable and layout
	int				termwidth;
	int				maxcol[LIST_MODE_COLUMNS]; // longest string for each column (-l)
	int				col_len; // longest string for normal output
	int				line_len; // position of the last char printed on current line
	int				totalblocks; // for -l
	int				print_initiated;

}				t_env;

/*
** ftls_init.c
*/
int				ftls_parse_cli_args(t_env *e, int ac, char **av);
int				ftls_init_env(t_env *e, char **av);
int				ftls_init_entry(t_entry *d);
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
int				ftls_manage_subdir(t_list *current, t_list **subdir, t_env *e);
void			ftls_elemdel(void *ptr, size_t size);

int				ftls_add_entry(t_list **alst, t_env *e, char *name,
		char *prefix);
void			ftls_copy_details(t_entry *dst, struct stat *src, char *name,
		char *prefix);


/*
**	ftls_sort.c
*/
int				ftls_compare_str(void *ref, void *run);
int				ftls_compare_type(void *ref, void *run);


/*
** ftls_process.c
*/
int				ftls_process_entry(t_env *e, char *name, char *prefix);
int				ftls_process_argnames(t_env *e);

t_list			*ftls_get_subdir(t_env *e, char *path);
void			ftls_recursion(t_env *e, t_list *subdir);

/*
** ftls_misc.c
*/

int				ftls_get_terminal_width(t_env *e);
int				ftls_isnavdot(char *name);
int				ftls_is_entry_eligible(t_env *e, t_entry *entptr);
int				ftls_is_entry_treatable(t_env *e, t_entry *entptr);

/*
** flts_print.c
*/
void			ftls_quick_ll(t_env *e, t_entry *d);
void			ftls_print_name(t_env *e, char *name);
char			*ftls_process_path(t_env *e, char *name, char *prefix);
void			ftls_print_dir(t_env *e, t_list *subdir);
void			ftls_print_entry(t_env *e, t_entry *entptr);
void			ftls_manage_spacing(t_env *e);

/*
** ftls_error.c
*/
void			ftls_print_usage_stderr(t_env *e);
int				ftls_print_error_illegal_option(t_env *e, char *progname,
				char option);

/*
** ftls_debug.c
*/
void			ftls_debug_show_args(t_env *e);
void			ftls_debug_show_list(t_list *lst);
void			ftls_debug_show_options(t_env *e);
void			ftls_debug_show_entry(t_entry *content);

/*
**	ftls_decode.c
*/
void			ftls_decode_type(mode_t st_mode, char *out);
void			ftls_decode_access_rights(mode_t st_mode, char *out);
void			ftls_decode_mode(mode_t st_mode);

#endif
