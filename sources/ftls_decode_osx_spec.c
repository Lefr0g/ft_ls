/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_decode_osx_spec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 16:16:12 by amulin            #+#    #+#             */
/*   Updated: 2016/08/24 16:16:47 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ftls_decode_type_osx(mode_t st_mode, char *out)
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

#ifdef __APPLE__

void	ftls_decode_extended_osx(char *out, char *path)
{
	acl_t	aclbuf;

	if (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0)
		out[10] = '@';
	else if ((aclbuf = acl_get_file(path, ACL_TYPE_EXTENDED)))
	{
		out[10] = '+';
		acl_free(aclbuf);
	}
	else
		out[10] = ' ';
}

#endif
