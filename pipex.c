/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:45:47 by anshovah          #+#    #+#             */
/*   Updated: 2023/07/19 21:59:43 by anshovah         ###   ########.fr       */
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

char	*ft_strcat_slash(char *src, char *dest)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (dest[len])
		len++;
	dest[len++] = '/';	
	while (src[i])
	{
		dest[len] = src[i];
		i++;
		len++;
	}
	dest[len] = 0;
	return (dest);
}

void	ft_first_command(char *cmd1, int fd, char **path_dirs)
{
	char	**argv;
	int		check;
	int		i;

	argv = ft_split(cmd1, NULL, 0, ' ');
	i = -1;
	while (path_dirs[++i])
		execve(ft_strcat_slash(argv[0], path_dirs[i]), argv, NULL);
}

int	main(int ac, char *av[], char *env[])
{
	char	**path_dirs;
	int		fd;

	path_dirs = ft_get_path(env);
	if (!ft_check_access(av[1]))
		return 1;
	fd = open(av[1], O_RDONLY);
	ft_first_command(av[2], fd, path_dirs);	
}
