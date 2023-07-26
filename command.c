/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:24:38 by anshovah          #+#    #+#             */
/*   Updated: 2023/07/25 16:26:32 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_find_command(char *cmd, char **path_dirs)
{
	int		check;
	int		mode;
	int		i;
	char	*path;

	mode = X_OK | F_OK;
	i = -1;
	while (path_dirs[++i])
	{
		path = ft_strjoin_slash(cmd, path_dirs[i]);
		check = access(path, mode);
		if (check == 0)
			return (path);
	}
	return (NULL);
}

char	*ft_strjoin_slash(char *src, char *dest)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
		j++;
	path = malloc(i + j + 2);			
	if (!path)
		return (NULL);
	i = -1;	
	while(dest[++i])
		path[i] = dest[i];
	path[i++] = '/';
	j = 0;
	while (src[j])
	{
		path[i] = src[j];
		i++;
		j++;
	}
	path[i] = 0;
	return (path);
}
