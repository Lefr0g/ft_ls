/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_sort_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 15:57:56 by amulin            #+#    #+#             */
/*   Updated: 2016/08/24 16:01:22 by amulin           ###   ########.fr       */
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
