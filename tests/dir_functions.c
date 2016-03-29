/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 17:48:53 by amulin            #+#    #+#             */
/*   Updated: 2016/03/28 17:52:30 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <dirent.h>
#include <sys/types.h>

int	main(int argc, char **argv)
{
	DIR	*dir;

	if (argc != 2)
	{
		ft_printf("usage: %s directory_name\n", argv[0]);
	}
	else
	{
		dir = opendir(argv[1]);
		if (!dir)
			ft_putstr("Main : couldn't open dir\n");
	}
}
