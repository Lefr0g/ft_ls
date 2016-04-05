/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 17:48:53 by amulin            #+#    #+#             */
/*   Updated: 2016/04/05 16:24:42 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <dirent.h>
#include <sys/types.h>

int	main(int argc, char **argv)
{
	int				i;
	DIR				*dir;
	struct dirent 	*d;

	if (argc != 2)
	{
		ft_printf("usage: %s directory_name\n", argv[0]);
	}
	else
	{
		dir = opendir(argv[1]);
		if (!dir)
			ft_putstr("Main : couldn't open dir\n");
		else
		{
			i = 0;
			d = readdir(dir);
			while (d)
			{
				ft_printf("%d (inode %d) : \033[33m%s\033[0m (%d)",
						i, d->d_ino, d->d_name, d->d_namlen);
				if (!d->d_type)
					ft_putstr(" (type unknown)");
				else if (d->d_type == DT_DIR)
					ft_putstr(" (directory)");
				else if (d->d_type == DT_LNK)
					ft_putstr(" (link)");
				else if (d->d_type == DT_REG)
					ft_putstr(" (regular file)");
				ft_printf(" (d_type = %d)", d->d_type);
				ft_putchar('\n');
				d = readdir(dir);
				i++;
			}
			if (closedir(dir))
				ft_putstr("ERROR : couldn't close directory stream\n");
		}
	}
}
