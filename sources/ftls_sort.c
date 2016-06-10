/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_list_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 19:01:35 by amulin            #+#    #+#             */
/*   Updated: 2016/06/09 20:28:58 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	A pointer to this function is used to sort the entry list by name
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
**	A pointer to this function is used to seprate regular files from the
**	others, and displace them to the beginning of the entry list
*/

int		ftls_compare_type(void *ref, void *run)
{
	mode_t	ref_mod;
	mode_t	run_mod;

	ref_mod = *(mode_t*)ref;
	run_mod = *(mode_t*)run;

	ft_printf("ref_mod = %b, run_mod = %b\n", ref_mod, run_mod);
//	ft_printf("%b\n", S_IFREG);
	if ((ref_mod & S_IFDIR) == S_IFDIR && (run_mod & S_IFDIR) != S_IFDIR)
	   return (1);
	ft_printf("-1 returned\n");
	return (-1);
}
