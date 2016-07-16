/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 16:45:18 by amulin            #+#    #+#             */
/*   Updated: 2016/06/14 18:40:08 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ftls_get_terminal_width(t_env *e)
{
	struct ttysize	s_ttsz;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &s_ttsz) == -1)
	{
		ft_print_error(e->progname, "ioctl()", errno);
		return (-1);
	}
	return (s_ttsz.ts_cols);
}

int		ftls_isnavdot(char *name)
{
	if (!ft_strcmp(name, ".") || !ft_strcmp(name, ".."))
		return (1);
	return (0);
}

/*
**	This function checks if the option set is compatible with the file name.
**	Flags managed by this funtion: -a -A
*/

int		ftls_is_entry_showable(t_env *e, t_entry *entptr)
{
	char	*ptr;

	ptr = *(entptr->name);
	if (ptr[0] != '.' || (ptr[0] == '.' &&
				(e->show_all_nodot || e->show_all)))
		if (ptr[0] != '.' || !(ftls_isnavdot(ptr)
					&& (e->show_all_nodot)))
			return (1);
	return (0);
}

int		ftls_is_entry_device(t_entry *d)
{
	if ((d->st_mode & S_IFREG) == S_IFREG)
		return (0);
	if ((d->st_mode & S_IFLNK) != S_IFLNK &&
			((d->st_mode & S_IFCHR) == S_IFCHR
			 || (d->st_mode & S_IFBLK) == S_IFBLK))
		return (1);
	return (0);
}

/*
**	Checks if the entry is a dir that must be treated.
**	This entry can also be a symbolic link.
**	Invalid entries : sockets.
*/

int		ftls_is_entry_treatable(t_env *e, t_entry *entptr)
{
	if ((entptr->st_mode & S_IFSOCK) == S_IFSOCK
			|| (entptr->st_mode & S_IFBLK) == S_IFBLK)
		return (0);
	if ((entptr->st_mode & S_IFDIR) == S_IFDIR)
		return (1);
	if (e->followlink_cli && e->iscli && (entptr->st_mode & S_IFLNK) == S_IFLNK)
		return (1);
	if (e->followlink_sub && (entptr->st_mode & S_IFLNK) == S_IFLNK)
		return (1);
	return (0);
}

/*
 * This function returns a malloced string containing the human-readable value
 * of the size passed as parameter.
 * NB: size off_t are int64
	1024 (K)
	1048576 (M)
	1073741024 (G)
	1099511627776 (T)
	The maximum size unit managed is Terabyte
*/
char	*ft_humanize_size(off_t size)
{
	char	*str;
	char	*buf;
	long	divider;
	char	unit[5] = {'T','G','M','K','B'};
	int		i;
	int		sizelen;

	int		rounded;

	i = 0;
	str = ft_strnew(100);
	sizelen = 1;
	divider = size;
	while ((divider = divider / 10) > 0)
		sizelen++;
	divider = 1099511627776;
	while (divider > 0)
	{
		if (size / divider)
		{
			if (divider > 1)
				buf = ft_itoa(size / divider);
			else
				buf = ft_itoa((int)size);
			ft_strcpy(str, buf);
			ft_strdel(&buf);
			if (divider > 1 && ft_strlen(str) == 1)
			{
				ft_strlcat(str, ".", 100);

				rounded = ft_get_first_rounded_digit(size, divider);
				buf = ft_itoa(rounded);

/*
				buf = ft_itoa(size % divider);
				if ((int)ft_strlen(buf) < sizelen - 1)
				{
//					if (buf[0] > 5 && (int)ft_strlen == sizelen - 1)
						ft_strncat(str, "1", 1);
//					else
//						ft_strncat(str, "0", 1);
				}
				else
				{
					if (ft_strlen(buf) >= 2)
						buf[2] = '\0';
					{
						if (ft_atoi(&buf[1]) > 5)
						{
							if (buf[0] < 9)
								buf[0] = buf[0] + 1;
							else
							{
								str[0] = str[0] + 1;
								buf[0] = '0';
							}
						}
					}
*/
					ft_strncat(str, buf, 1);
		//		}
				ft_strdel(&buf);
			}
			ft_strncat(str, &unit[i], 1);
			return (str);
		}
		if (divider >= 1)
			divider = divider / 1024;
		i++;
	}
	return (str);
}

/*
 * NB: do it recursive
 * ex: 1042    1067
 * 	   |	   |
 * 	  1.0	  1.1
 * ALGO
 * 	- Obtenir rest = nbr % divider
 * 	- Si len(rest) == len(nbr) - 2
 * 		- Comparer chiffre suivant
 * 			- Si > 5, retourner 1
 * 			- Sinon, retourner 0
 * 	- Sinon is len(rest) == len(nbr) - 1
 * 		- Retourner rest / 10
 * 	- Sinon
 * 		- Retourner 0
*/
int	ft_get_first_rounded_digit(double nbr, int divider)
{
	long	rest;
	char	*reststr;
	char	*nbrstr;
	int		result;

	if (!divider)
		return (-1);
	nbrstr = ft_itoa_ll(nbr, 10);
	rest = (int)nbr % (int)divider;
	reststr = ft_itoa_ll(rest, 10);
	if (ft_strlen(reststr) == ft_strlen(nbrstr) - 1)
		result = rest / 10;
	else if (ft_strlen(reststr) == ft_strlen(nbrstr) - 2)
	{
		rest %= 10;
		if (rest / 10 > 5)
			result = 1;
		else
			result = 0;
	}
	else
		result = 0;
	ft_strdel(&reststr);
	ft_strdel(&nbrstr);
	return (result);
}
