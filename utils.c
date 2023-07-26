/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:09:00 by anshovah          #+#    #+#             */
/*   Updated: 2023/07/25 17:10:37 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_check_access(char *path)
{
	int	check;
	int	mode;

	mode = R_OK | F_OK;
	check = access(path, mode);
	if (check == 0)
		return (1);
	else
		return (0);	
}

void	ft_free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free (arr);	
}
