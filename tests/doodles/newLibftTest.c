/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newLibftTest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 20:29:37 by amulin            #+#    #+#             */
/*   Updated: 2016/03/28 20:33:30 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	main(void)
{
	ft_putstr("VA > printed with ft_putstr()\n");
	ft_putwstr(L"XT > printed with ft_putwstr()\n");
	ft_printf("FTPF > printed with ft_printf()\n");
	ft_print_error(" ", "ER > printed with ft_print_error()\n", 0);

	return (0);
}
