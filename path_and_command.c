/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_and_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:24:38 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/02 20:57:55 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_get_path(char *env[])
{
	char	*path;
	char	*abs_path;
	char	**path_dirs;
	int		skip;

	path = "PATH=";
	skip = 5;
	abs_path = ft_find_path(env, path);
	abs_path += skip;
	path_dirs = ft_split(abs_path, ':');
	if (!path_dirs)
		return (NULL);
	return (path_dirs);
}

char	*ft_find_path(char *env[], char *path)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(path, env[i], 5))
			return (env[i]);
	return (NULL);
}

char	*ft_find_command(char *cmd, char **path_dirs)
{
	int		check;
	int		mode;
	int		i;
	char	*path;

	mode = X_OK | F_OK;
	i = -1;
	if (ft_strchr(cmd, '/') != NULL)
	{
		check = access(cmd, mode);
		if (check == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	while (path_dirs[++i])
	{
		path = ft_strjoin_slash(cmd, path_dirs[i]);
		check = access(path, mode);
		if (check == 0)
			return (path);
		else
			free(path);
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
	j = -1;
	while (src[++j])
	{
		path[i] = src[j];
		i++;
	}
	path[i] = 0;
	return (path);
}
