/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_decode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 19:34:49 by amulin            #+#    #+#             */
/*   Updated: 2016/06/08 19:35:23 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ftls_decode_type(mode_t st_mode, char *out)
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

void	ftls_decode_access_rights(mode_t st_mode, char *out)
{
	int		i;
	mode_t	mask;

	mask = S_IRUSR;
	i = 0;
	while (i <= 6)
	{
		out[1 + i] = st_mode & mask ? 'r' : '-';
		out[2 + i] = st_mode & (mask >> 1) ? 'w' : '-';
		out[3 + i] = st_mode & (mask >> 2) ? 'x' : '-';
		mask >>= 3;
		i += 3;
	}
}

void	ftls_decode_mode(mode_t st_mode)
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
