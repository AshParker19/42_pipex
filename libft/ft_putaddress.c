/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:36:01 by anshovah          #+#    #+#             */
/*   Updated: 2023/05/03 19:21:16 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putaddress(unsigned long addr, int *len)
{
	if (!addr)
		ft_putstr("(nil)", len);
	else
	{
		if (addr < 16)
		{
			ft_putstr("0x", len);
			ft_putchar(HEX_LOWER[addr % 16], len);
			return ;
		}
		ft_putaddress(addr / 16, len);
		ft_putchar(HEX_LOWER[addr % 16], len);
	}
}
