/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:45:47 by anshovah          #+#    #+#             */
/*   Updated: 2023/07/20 19:29:07 by anshovah         ###   ########.fr       */
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

void	ft_first_command(char *cmd1, int infile_fd, char **path_dirs, int fd[])
{
	char	**argv;
	int		check;
	int		i;

	close(fd[0]);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	argv = ft_split(cmd1, NULL, 0, ' ');
	i = -1;
	while (path_dirs[++i])
		execve(ft_strcat_slash(argv[0], path_dirs[i]), argv, NULL);
	
}

void	ft_second_command(char *cmd2, int outfile_fd, char **path_dirs, int fd[])
{
	int		i;
	char	**argv;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(fd[0]);
	wait(NULL);
	argv = ft_split(cmd2, NULL, 0, ' ');
	i = -1;
	while (path_dirs[++i])
		execve(ft_strcat_slash(argv[0], path_dirs[i]), argv, NULL);
}

int	main(int ac, char *av[], char *env[])
{
	char	**path_dirs;
	int		infile_fd;
	int		outfile_fd;
	int		fd[2];
	int		pid;
	int		pipe_check;

	if (ac != 5 || (!*av[0] || !*av[1] || !*av[2] || !*av[3] || !*av[4]))
	{
		write(2, "Wrong arguments!\n", 18);
		return (ARGUMENT_ERROR);
	}
	path_dirs = ft_get_path(env);
	if (!ft_check_access(av[1]))
	{
		perror("access");
		return (ACCESS_ERROR);
	}
	infile_fd = open(av[1], O_RDONLY);
	if (infile_fd < 0)
	{
		perror("open");
		return (OPEN_ERROR);
	}
	pipe_check = pipe(fd);
	if (pipe_check < 0)
	{
		perror("pipe");
		return (PIPE_ERROR);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (FORK_ERROR);
	}
	if (pid == 0)
		ft_first_command(av[2], infile_fd, path_dirs, fd);
	else
	{
		outfile_fd = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (outfile_fd < 0)
		{
		perror("open");
		return (OPEN_ERROR);
		}
		ft_second_command(av[3], outfile_fd, path_dirs, fd);
		close(infile_fd);
		close(outfile_fd);
	}	
}

// redirect the content of infile as an input of cmd1

// check if any of the arguments are not empty strings

