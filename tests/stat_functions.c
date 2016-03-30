/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 17:25:27 by amulin            #+#    #+#             */
/*   Updated: 2016/03/30 13:58:44 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <sys/stat.h>
#include <errno.h>

#include <time.h>

//#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
//#include <uuid/uuid.h>



int	main(int argc, char **argv)
{
	struct stat		buf;
	struct passwd	*pass;
	struct group	*grp;

#ifndef _DARWIN_FEATURE_64_BIT_INODE
	ft_printf("_DARWIN_FEATURE_64_BIT_INODE is not defined\n");
#endif

	if (argc != 2)
	{
		ft_printf("usage: %s file_name\n", argv[0]);
	}
	else
	{
		if (stat(argv[1], &buf))
			ft_printf("\033[31mERROR\033[0m : could not stat() file named %s (%s)\n", argv[1], strerror(errno));
		else
		{
			ft_printf("\nStat() succeeded on \033[32m%s\033[0m\n", argv[1]);
			ft_putstr("Here is the raw stat structure:\n");
			ft_print_memory(&buf, sizeof(struct stat));
			ft_putchar('\n');
			
			ft_printf("ID of device containing file: \033[33m%d\033[0m\n", buf.st_dev);
			ft_printf("Device ID: \033[33m%d\033[0m\n", buf.st_rdev);
			ft_printf("Inode: \033[33m%d\033[0m\n", buf.st_ino);
			ft_printf("Mode: \033[33m%d\033[0m\n", buf.st_mode);
			ft_printf("Mode (bin): \033[33m%b\033[0m\n", buf.st_mode);
			ft_printf("# of hard links: \033[33m%d\033[0m\n", buf.st_nlink);


			ft_printf("File UID: \033[33m%d\033[0m\n", buf.st_uid);
			if (!(pass = getpwuid(buf.st_uid)))
				ft_putstr("ERROR: could not resolve user name\n");
			ft_printf("File owner: \033[33m%s\033[0m\n", pass->pw_name);	
			ft_printf("File owner's encryptedf pw: \033[33m%s\033[0m\n", pass->pw_passwd);
			ft_putstr("Here is the raw passwd structure:\n");
			ft_print_memory(pass, sizeof(struct passwd));
			ft_putchar('\n');

			
			ft_printf("File GID: \033[33m%d\033[0m\n", buf.st_gid);
			if (!(grp = getgrgid(buf.st_gid)))
				ft_putstr("ERROR: could not resolve group name\n");
			ft_printf("File group: \033[33m%s\033[0m\n", grp->gr_name);

			ft_printf("Time of last access: \033[33m%d\033[0m\n", buf.st_atimespec);
			ft_printf("Time of last access (formatted): \033[33m%s\033[0m\n",
					ctime(&(buf.st_atime)));
			ft_printf("Time of last modif: \033[33m%d\033[0m\n", buf.st_mtimespec);
			ft_printf("Time of last status change: \033[33m%d\033[0m\n", buf.st_ctimespec);
			ft_printf("File size: \033[33m%d\033[0m bytes\n", buf.st_size);
		}
	}
}
