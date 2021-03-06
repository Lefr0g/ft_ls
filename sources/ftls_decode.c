/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_decode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 19:34:49 by amulin            #+#    #+#             */
/*   Updated: 2016/08/24 16:16:50 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ftls_decode_type_linux(mode_t st_mode, char *out)
{
	if ((st_mode & S_IFSOCK) == S_IFSOCK)
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

void	ftls_decode_mode(mode_t st_mode, char *out)
{
	ft_bzero(out, 12);
	FTLS_DECODE_TYPE(st_mode, out);
	ftls_decode_access_rights(st_mode, out);
	ftls_decode_special_bits(st_mode, out);
}

void	ftls_decode_special_bits(mode_t st_mode, char *out)
{
	if ((st_mode & S_ISVTX) == S_ISVTX)
	{
		if (out[9] == 'x')
			out[9] = 't';
		else
			out[9] = 'T';
	}
	if ((st_mode & S_ISUID) == S_ISUID)
	{
		if (out[3] == 'x')
			out[3] = 's';
		else
			out[3] = 'S';
	}
	if ((st_mode & S_ISGID) == S_ISGID)
	{
		if (out[6] == 'x')
			out[6] = 's';
		else
			out[6] = 'S';
	}
}
