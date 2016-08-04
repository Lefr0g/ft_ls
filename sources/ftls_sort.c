/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_list_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 19:01:35 by amulin            #+#    #+#             */
/*   Updated: 2016/07/26 19:06:44 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	A pointer to this function is used to sort the entry list by name under OSX
*/

int		ftls_compare_str(void *ref, void *run)
{
	char	***ref_str;
	char	***run_str;

	ref_str = (char***)ref;
	run_str = (char***)run;
	return (ft_strcmp(**ref_str, **run_str));
}

/*
**	This variant is used to sort the entry list by name under linux
**	The difference is the absence of case-sensitivity
*/

char	*ftls_strtolower(char *str)
{
	char	*ret;
	int		i;

	ret = ft_strdup(str);
	i = -1;
	while (str[++i])
		if (str[i] >= 'A' && str[i] <= 'Z')
			ret[i] = str[i] + 32;
	return (ret);
}

int		ftls_compare_str_linux(void *ref, void *run)
{
	char	*ref_lowered;
	char	*run_lowered;
	int		result;

	ref_lowered = ftls_strtolower(**(char***)ref);
	run_lowered = ftls_strtolower(**(char***)run);
	result = ft_strcmp(ref_lowered, run_lowered);
	ft_strdel(&ref_lowered);
	ft_strdel(&run_lowered);
	return (result);
}


/*
**	A pointer to this function is used to seprate regular files from the
**	others, and displace them to the beginning of the entry list
*/

int		ftls_compare_type(void *ref, void *run)
{
	mode_t	ref_mod;
	mode_t	run_mod;

	ref_mod = *(mode_t*)ref;
	run_mod = *(mode_t*)run;
	if ((ref_mod & S_IFDIR) == S_IFDIR && (run_mod & S_IFDIR) != S_IFDIR)
		return (1);
	return (-1);
}

/*
**	Timestamp comparison for Darwin
**	If seconds are equal, then we compare the nanoseconds
*/

int		ftls_compare_date_osx(void *ref, void *run)
{
	TIME_TYPE	ref_time;
	TIME_TYPE	run_time;

	ref_time = *(struct timespec*)ref;
	run_time = *(struct timespec*)run;
	if (ref_time.tv_sec < run_time.tv_sec)
		return (1);
	if (ref_time.tv_sec > run_time.tv_sec)
		return (-1);
	else
		return (run_time.tv_nsec - ref_time.tv_nsec);
}

/*
**	Timestamp comparison for linux
*/

int		ftls_compare_date_linux(void *ref, void *run)
{
	time_t	ref_time;
	time_t	run_time;

	ref_time = *(time_t*)ref;
	run_time = *(time_t*)run;
	return (run_time - ref_time);
}

/*
**	Size comparison
*/

int		ftls_compare_size(void *ref, void *run)
{
	off_t	ref_size;
	off_t	run_size;

	ref_size = *(off_t*)ref;
	run_size = *(off_t*)run;
	return (run_size - ref_size);
}
