/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:57:07 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/03 16:58:59 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	c1;

	i = 0;
	c1 = c;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c1)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == c1)
		return ((char *)s + i);
	return (NULL);
}
