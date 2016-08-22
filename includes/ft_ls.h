/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 10:52:12 by amulin            #+#    #+#             */
/*   Updated: 2016/07/28 21:11:24 by amulin           ###   ########.fr       */
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
#  define FTLS_PARSE_CLI_ARGS ftls_parse_cli_args_osx
#  define FTLS_COMPARE_DATE ftls_compare_date_osx
#  define FTLS_PRINT_LISTED ftls_quick_ll_osx
#  define FTLS_DECODE_TYPE ftls_decode_type_osx
#  define FTLS_MANAGE_SORTING ftls_manage_sorting_osx
#  include <sys/acl.h>
#  include <uuid/uuid.h>
# elif __linux__
#  define TIME_TYPE struct timespec
#  define FTLS_ATIME	st_atim
#  define FTLS_MTIME	st_mtim
#  define FTLS_CTIME	st_ctim
#  define FTLS_PARSE_CLI_ARGS ftls_parse_cli_args_linux
#  define FTLS_COMPARE_DATE ftls_compare_date_linux
#  define FTLS_PRINT_LISTED ftls_quick_ll_linux
#  define FTLS_DECODE_TYPE ftls_decode_type_linux
#  define FTLS_MANAGE_SORTING ftls_manage_sorting_linux
#  define S_IFWHT 0
#  include <linux/nfsacl.h>
# endif

# include <sys/stat.h>
# include <sys/xattr.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

# include <sys/ioctl.h>

# include <sys/types.h>

# define OPT_ARRAY_SIZE 16
# define LIST_MODE_COLUMNS 9
# define LINK_NAME_LEN 1025

typedef struct	s_entry
{
	char					**name;
	char					**prefix;
	char					**linktarget;
	ino_t					st_inode;
	mode_t					st_mode;
	mode_t					st_mode_ptr[1];
	nlink_t					st_nlink;
	uid_t					st_uid;
	char					**pw_name;
	char					**gr_name;
	gid_t					st_gid;
	dev_t					st_rdev;
	TIME_TYPE				st_atimespec;
	TIME_TYPE				st_mtimespec;
	TIME_TYPE				st_ctimespec;
	TIME_TYPE				st_time_ptr[1];

	off_t					st_size;
	off_t					st_size_ptr[1];
	char					**size_str;
	int						st_blocks;

}				t_entry;

/*
**	show_all_nodot	-> starting with . except "." and .. (for -A)
**	show_all_nodot	->  starting with . except "." and .. (for -A)
**	show_all 		-> All including "." and .. (for -a)
**	show_num_id		-> flag for -n
**	recursive		-> flag for -R
**	reverse			-> flag for -r
**	sort_none		-> flag for -f
**	sort_size		-> flag for -S
**	*
**	sort_time		-> trigger flag for time sorting
**	sort_time_val	-> Indicates what time value to be used for sorting
**	*
**	human			-> flag for -h
**	showinode		-> flag for -i
**	*
**	output_val		-> temporary flag for -l and -1used during option parsing
**	showlist		-> flag for -l
**	oneperline		-> flag for -1
**	*
**	followlink_cli	-> If link given as argument, follow it unless -l w/out -L
**	followlink_sub	-> In case of -R, follow links entries. (for -L)
**	*
**	termwidth		-> number of columns in active terminal
**	maxcol[LIST_MODE_COLUMNS] -> longest string for each column (used for -l)
**	col_len			-> longest string for normal output (not -l)
**	line_len		-> position of the last char printed on current line
**	totalblocks		-> used for -l
**	atleastonetoshow -> print status flag
**	print_initiated -> printing status flag
**	iscli			-> to differenciate program arguments from default situation
*/
typedef struct	s_env
{
	t_list			*lst;
	char			*progname;
	char			*supported_option[OPT_ARRAY_SIZE];
	char			**cli_option;
	char			**cli_notopt;
	char			abort;

	char			show_all_nodot;
	char			show_all;
	char			show_num_id;
	char			recursive;
	char			reverse;
	char			sort_none;
	char			sort_size;

	char			sort_time;
	char			sort_time_val;

	char			human;
	char			showinode;

	char			output_val;
	char			showlist;
	char			oneperline;

	char			followlink_cli;
	char			followlink_sub;

	int				termwidth;
	int				maxcol[LIST_MODE_COLUMNS];
	int				col_len;
	int				line_len;
	int				totalblocks;
	int				atleastonetoshow;
	int				print_initiated;
	char			iscli;
}				t_env;

/*
**	To be added to libft
*/

/*
**	ftls_init.c
*/
int				ftls_parse_cli_args_osx(t_env *e, int ac, char **av);
int				ftls_parse_cli_args_linux(t_env *e, int ac, char **av);
int				ftls_init_env(t_env *e, char **av);
int				ftls_init_entry(t_entry *d);
int				ftls_init_options(t_env *e);
void			ftls_manage_options_priorities(t_env *e);

/*
**	ftls_del.c
*/
int				ftls_free_all(t_env *e);
void			ftls_elemdel(void *ptr, size_t size);
void			ftls_strdelnfree(char **str);

/*
**	main.c
*/
int				ftls_isdir(char *path, char *progname, int verbose);
int				ftls_isfile(char *path, char *progname, int verbose);

/*
**	ftls_list.c
*/
int				ftls_add_entry(t_list **alst, t_env *e, char *name,
		char *prefix);
void			ftls_copy_details(t_entry *dst, struct stat *src, char *name,
		char *prefix);
void			ftls_copy_details_sub1(t_entry *dst, struct stat *src);
void			ftls_copy_details_sub2(t_env *e, t_entry *dst,
		struct stat *src);
void			ftls_manage_sorting_osx(t_env *e, t_list **list);
void			ftls_manage_sorting_linux(t_env *e, t_list **list);

/*
**	ftls_list_sub.c
*/
void			ftls_get_column_metadata(t_env *e, t_entry *d);
void			ftls_get_linktarget(t_entry *dst, char *path);
int				ftls_get_file_status(t_env *e, struct stat *statbuf,
		char **path);
void			ftls_gen_size_str(t_env *e, t_entry *d);
void			ftls_manage_time_ptr(t_env *e, t_entry *dst);

/*
**	ftls_sort.c
*/
int				ftls_compare_str(void *ref, void *run);
int				ftls_compare_str_linux(void *ref, void *run);
int				ftls_compare_type(void *ref, void *run);
int				ftls_compare_date_osx(void *ref, void *run);
int				ftls_compare_date_linux(void *ref, void *run);
int				ftls_compare_size(void *ref, void *run);

/*
**	ftls_process.c
*/
int				ftls_process_entry(t_env *e, char *name, char *prefix);
int				ftls_process_argnames(t_env *e);
t_list			*ftls_get_subdir(t_env *e, char *name, char *path);
void			ftls_recursion(t_env *e, t_list *subdir);

/*
**	ftls_misc.c
*/

int				ftls_get_terminal_width(t_env *e);
int				ftls_isnavdot(char *name);
int				ftls_is_entry_showable(t_env *e, t_entry *entptr);
int				ftls_is_entry_treatable(t_env *e, t_entry *entptr);
int				ftls_is_entry_device(t_entry *d);

/*
**	flts_print_1.c
*/
char			*ftls_gen_timestr(t_env *e, t_entry *d);
void			ftls_quick_ll_osx(t_env *e, t_entry *d);
void			ftls_quick_ll_linux(t_env *e, t_entry *d);
void			ftls_quick_ll_print_dev_or_size(t_env *e, t_entry *d);
void			ftls_quick_ll_sub_common(t_env *e, t_entry *d, char *out);

/*
**	ftls_print_2.c
*/
void			ftls_print_name(t_env *e, char *name);
char			*ftls_process_path(t_env *e, char *name, char *prefix);
void			ftls_print_dir(t_env *e, t_list *subdir);
void			ftls_print_entry(t_env *e, t_entry *entptr);
void			ftls_manage_spacing(t_env *e);

/*
**	ftls_error.c
*/
void			ftls_print_usage_stderr(t_env *e);
int				ftls_print_error_illegal_option(t_env *e, char *progname,
				char option);

/*
**	ftls_debug.c
*/
void			ftls_debug_show_args(t_env *e);
void			ftls_debug_show_list(t_list *lst);
void			ftls_debug_show_options(t_env *e);
void			ftls_debug_show_entry(t_entry *content);

/*
**	ftls_decode.c
*/
void			ftls_decode_type_osx(mode_t st_mode, char *out);
void			ftls_decode_type_linux(mode_t st_mode, char *out);
void			ftls_decode_access_rights(mode_t st_mode, char *out);
void			ftls_decode_mode(mode_t st_mode, char *out);
void			ftls_decode_special_bits(mode_t st_mode, char *out);
void			ftls_decode_extended_osx(char *out, char *path);

#endif
