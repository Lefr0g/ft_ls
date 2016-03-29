/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 17:25:27 by amulin            #+#    #+#             */
/*   Updated: 2016/03/29 17:38:36 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <sys/stat.h>
#include <errno.h>

int	main(int argc, char **argv)
{
	struct stat	*buf;

	buf = NULL;
	if (argc != 2)
	{
		ft_printf("usage: %s file_name\n", argv[0]);
	}
	else
	{
		if (stat(argv[1], buf))
			ft_printf("ERROR : could not stat() this file (%s)\n", strerror(errno));
		else
		{
			ft_printf("Inode: %d\n", buf->st_ino);
		}
	}
}
