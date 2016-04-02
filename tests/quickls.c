/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quickls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 17:25:27 by amulin            #+#    #+#             */
/*   Updated: 2016/04/02 19:00:06 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <dirent.h>

#include <sys/stat.h>
#include <errno.h>

#include <time.h>

//#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
//#include <uuid/uuid.h>

#include <stdio.h>

#include <sys/xattr.h>

#include <sys/acl.h>

#define TEST_IFDIR	0040000
#define TEST_IFDIR_SHORT	0040

void	exit_on_error(char *progname, char *arg, int errnum)
{
	ft_printf("%s: %s: %s\n", progname, arg, strerror(errnum));
	exit(0);
}

static void	ftls_decode_type(mode_t st_mode, char *out)
{
	if ((st_mode & S_IFWHT) == S_IFWHT)
		out[0] = 'w';
	else if ((st_mode & S_IFSOCK) == S_IFSOCK)
		out[0] = 's';
	else if ((st_mode & S_IFLNK) == S_IFLNK)
		out[0] = 'l';
	else if ((st_mode & S_IFREG) == S_IFREG)
		out[0] = '-';
	else if ((st_mode & S_IFBLK) == S_IFBLK)
		out[0] = 'b';
	else if ((st_mode & S_IFDIR) == S_IFDIR)
		out[0] = 'd';
	else if ((st_mode & S_IFCHR) == S_IFCHR)
		out[0] = 'c';
	else if ((st_mode & S_IFIFO) == S_IFIFO)
		out[0] = 'p';
}

static void	ftls_decode_access_rights(mode_t st_mode, char *out)
{
	int		i;
	mode_t	read_mask;
	mode_t	write_mask;
	mode_t	exec_mask;

	read_mask = S_IRUSR;
	write_mask = S_IWUSR;
	exec_mask = S_IXUSR;
	i = 0;
	while (i <= 6)
	{
		out[1 + i] = st_mode & read_mask ? 'r' : '-';
		out[2 + i] = st_mode & write_mask ? 'w' : '-';
		out[3 + i] = st_mode & exec_mask ? 'x' : '-';
		i += 3;
		read_mask >>= 3;
		write_mask >>= 3;
		exec_mask >>= 3;
	}
}

static void	ftls_decode_mode(mode_t st_mode)
{
	char	out[12];

	ft_bzero(out, 12);
	ft_putstr("\033[34m");
	ftls_decode_type(st_mode, out);
	ftls_decode_access_rights(st_mode, out);
	if ((st_mode & S_ISVTX) == S_ISVTX)
		out[9] = 't';
	ft_putstr(out);
	ft_putstr("\033[0m");
}

int	main(int argc, char **argv)
{
	DIR				*dir;
	struct dirent	*dirent;
	struct stat		statbuf;
	struct passwd	*passbuf;
	struct group	*groupbuf;
	char			*namebuf;
	char			*xattrnamebuf;
	int				xattrnamebuflen;
	char			*time;
	char			*buf;

/*
	ft_printf("S_IRWXU = %d,\t %b\n", S_IRWXU, S_IRWXU);
	ft_printf("S_IRWXG = %d,\t %b\n", S_IRWXG, S_IRWXG);
	ft_printf("S_IRWXO = %d,\t %b\n", S_IRWXO, S_IRWXO);
*/

/*
	ft_printf("IFDIR = %d, SHORT = %d\n", TEST_IFDIR, TEST_IFDIR_SHORT);
	ft_printf("S_IFIFO = %b\n", S_IFIFO);
	ft_printf("S_IFCHR = %b\n", S_IFCHR);
	ft_printf("S_IFDIR = %b\n", S_IFDIR);
	ft_printf("S_IFBLK = %b\n", S_IFBLK);
	ft_printf("S_IFREG = %b\n", S_IFREG);
	ft_printf("S_IFLNK = %b\n", S_IFLNK);
	ft_printf("S_IFSOCK= %b\n", S_IFSOCK);
	ft_printf("S_IFWHT = %b\n", S_IFWHT);
*/

	xattrnamebuflen = 512;
	xattrnamebuf = ft_strnew(xattrnamebuflen);
#ifndef _DARWIN_FEATURE_64_BIT_INODE
	ft_printf("_DARWIN_FEATURE_64_BIT_INODE is not defined\n");
#endif

	if (argc < 2)
	{
		ft_printf("usage: %s file_name\n", argv[0]);
	}
	else
	{
		if (!(dir = opendir(argv[1])))
			exit_on_error(argv[0], argv[1], errno);
		else
		{
			while ((dirent = readdir(dir)))
			{
				namebuf = ft_strjoin(argv[1], "/");
				namebuf = ft_strjoin(namebuf, dirent->d_name);
				if (lstat(namebuf, &statbuf))
					exit_on_error(argv[0], namebuf, errno);
				if (dirent->d_name[0] != '.')
				{
					ftls_decode_mode(statbuf.st_mode);

//					ft_printf("dirent->d_type = %d ", dirent->d_type);

					if (listxattr(namebuf, xattrnamebuf,
								xattrnamebuflen, XATTR_NOFOLLOW) > 0)
						ft_putstr("\033[32m@\033[0m ");
					else if (acl_get_file(namebuf, ACL_TYPE_EXTENDED))
						ft_putstr("\033[35m+\033[0m ");
					else
						ft_putstr("  ");
					buf = ctime(&(statbuf.st_mtime));
					buf = ft_strsub(buf, 0, ft_strlen(buf) - 9);
					time = ft_strsub(buf, 4, ft_strlen(buf));
					passbuf = getpwuid(statbuf.st_uid);
					groupbuf = getgrgid(statbuf.st_gid);
					ft_printf("%3d ", statbuf.st_nlink);
					ft_printf("%s\t%s\t", passbuf->pw_name, groupbuf->gr_name);
					ft_printf("%5d ", statbuf.st_size);
					ft_printf("%s ", time);
					ft_printf("%s\n", dirent->d_name);
				}
			}
			ft_printf("");
		}
		closedir(dir);
	}
}
