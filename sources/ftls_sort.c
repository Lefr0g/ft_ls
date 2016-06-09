/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_list_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 19:01:35 by amulin            #+#    #+#             */
/*   Updated: 2016/06/09 19:02:29 by amulin           ###   ########.fr       */
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
