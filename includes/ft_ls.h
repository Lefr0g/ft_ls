/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 10:52:12 by amulin            #+#    #+#             */
/*   Updated: 2016/06/28 18:08:18 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "libft_extra.h"
# include <dirent.h>

# ifdef __APPLE__
#  define TIME_TYPE struct timespec
#  define FTLS_ATIME	st_atimespec
#  define FTLS_MTIME	st_mtimespec
#  define FTLS_CTIME	st_ctimespec
#  define FTLS_COMPARE_DATE ftls_compare_date_osx
#  define FTLS_PRINT_LISTED ftls_quick_ll_osx
#  include <sys/acl.h>
#  include <uuid/uuid.h>
# elif __linux__
//#  define TIME_TYPE time_t
#  define TIME_TYPE struct timespec
#  define FTLS_ATIME	st_atim
#  define FTLS_MTIME	st_mtim
#  define FTLS_CTIME	st_ctim
#  define FTLS_COMPARE_DATE ftls_compare_date_linux
#  define FTLS_PRINT_LISTED ftls_quick_ll_linux
#  include <linux/nfsacl.h>
# endif


# include <sys/stat.h>

# include <sys/xattr.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

// Used to get terminal size
# include <sys/ioctl.h>

// Optional ?
# include <sys/types.h>

# define OPT_ARRAY_SIZE 16
# define LIST_MODE_COLUMNS 7
# define LINK_NAME_LEN 1025

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
	char					**linktarget;
//	char					iscli; // 1 if this entry is a cli argument
	ino_t					st_inode;
	mode_t					st_mode;
	mode_t					st_mode_ptr[1];
	nlink_t					st_nlink;
	uid_t					st_uid;
	gid_t					st_gid;
	dev_t					st_rdev;
	TIME_TYPE				st_atimespec; // last access
	TIME_TYPE				st_mtimespec; // last modification
	TIME_TYPE				st_ctimespec; // last status change
	TIME_TYPE				st_time_ptr[1];

	off_t					st_size; // in bytes
	off_t					st_size_ptr[1];
	int						st_blocks;

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
	char			show_num_id; // (for -n)
	char			recursive; // (for -R)
	char			reverse; // (for -r)
	char			sort_none; // (for -f)
	char			sort_size; // (for -S)

	/////////////////////////// TBD
	char			sort_timemod; // (for -t)
	char			sort_timech; // (for -c)
	char			sort_timeacc; // (for -u)

	char			sort_time; // Replacement (for -t)
	char			sort_time_val; // Experimental

	char			human; // (for -h)
//	char			color; // (for -G) (pas sur, semble trop time-consuming)
	char			showinode; // (for -i)
	char			showlist; // (for -l)
	char			oneperline; // (for -1)
	char			followlink_cli; // If a link is given as argument, follow it
//									unless -l given without -L
	char			followlink_sub; // In case of -R, follow links entries. (for -L)

	//				I/O data for human readable and layout
	int				termwidth;
	int				maxcol[LIST_MODE_COLUMNS]; // longest string for each column (-l)
	int				col_len; // longest string for normal output
	int				line_len; // position of the last char printed on current line
	int				totalblocks; // for -l
	int				atleastonetoshow;
	int				print_initiated;
	char			iscli;

}				t_env;

/*
** ftls_init.c
*/
int				ftls_parse_cli_args(t_env *e, int ac, char **av);
int				ftls_init_env(t_env *e, char **av);
int				ftls_init_entry(t_entry *d);
int				ftls_init_options(t_env *e);
int				ftls_free_all(t_env *e);
void			ftls_manage_options_priorities(t_env *e);

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
void			ftls_copy_details_sub(t_entry *dst, struct stat *src);
void			ftls_manage_time_ptr(t_env *e, t_entry *dst);
void			ftls_get_linktarget(t_entry *dst, char *path);
int				ftls_get_file_status(t_env *e, struct stat *statbuf, char **path);


/*
**	ftls_sort.c
*/
int				ftls_compare_str(void *ref, void *run);
int				ftls_compare_type(void *ref, void *run);
int				ftls_compare_date_osx(void *ref, void *run);
int				ftls_compare_date_linux(void *ref, void *run);
int				ftls_compare_size(void *ref, void *run);
void			ftls_manage_sorting(t_env *e, t_list **list);


/*
** ftls_process.c
*/
int				ftls_process_entry(t_env *e, char *name, char *prefix);
int				ftls_process_argnames(t_env *e);

t_list			*ftls_get_subdir(t_env *e, char *name, char *path);
void			ftls_recursion(t_env *e, t_list *subdir);

/*
** ftls_misc.c
*/

int				ftls_get_terminal_width(t_env *e);
int				ftls_isnavdot(char *name);
int				ftls_is_entry_showable(t_env *e, t_entry *entptr);
int				ftls_is_entry_treatable(t_env *e, t_entry *entptr);
int				ftls_is_entry_device(t_entry *d);

/*
** flts_print.c
*/
void			ftls_quick_ll_osx(t_env *e, t_entry *d);
void			ftls_quick_ll_linux(t_env *e, t_entry *d);
void			ftls_print_name(t_env *e, char *name);
char			*ftls_process_path(t_env *e, char *name, char *prefix);
void			ftls_print_dir(t_env *e, t_list *subdir);
void			ftls_print_entry(t_env *e, t_entry *entptr);
void			ftls_manage_spacing(t_env *e);
char			*ftls_gen_timestr(t_env *e, t_entry *d);

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
