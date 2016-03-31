/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quickls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 17:25:27 by amulin            #+#    #+#             */
/*   Updated: 2016/03/30 13:58:44 by amulin           ###   ########.fr       */
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

void	exit_on_error(char *progname, char *arg, int errnum)
{
	ft_printf("%s: %s: %s\n", progname, arg, strerror(errnum));
	exit(0);
}

int	main(int argc, char **argv)
{
	DIR				*dir;
	struct dirent	*dirent;
	struct stat		statbuf;
	struct passwd	*passbuf;
	struct group	*groupbuf;
	char			*namebuf;
	char			*time;
	char			*buf;

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
				if (stat(namebuf, &statbuf))
					exit_on_error(argv[0], namebuf, errno);
				if (ft_strcmp(".", dirent->d_name)
						&& ft_strcmp("..", dirent->d_name))
				{
					buf = ctime(&(statbuf.st_mtime));
					buf = ft_strsub(buf, 0, ft_strlen(buf) - 9);
					time = ft_strsub(buf, 4, ft_strlen(buf));
					passbuf = getpwuid(statbuf.st_uid);
					groupbuf = getgrgid(statbuf.st_gid);
					ft_printf("%d ", statbuf.st_nlink);
					ft_printf("%s %s ", passbuf->pw_name, groupbuf->gr_name);
					ft_printf("%d ", statbuf.st_size);
					ft_printf("%s ", time);
					ft_printf("%s\n", dirent->d_name);
				}
			}
			ft_printf("");
		}
		closedir(dir);
	}
}
