/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:45:47 by anshovah          #+#    #+#             */
/*   Updated: 2023/07/21 17:56:30 by anshovah         ###   ########.fr       */
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

void	ft_first_command(char *cmd1, int infile_fd, char **path_dirs, int fd[])
{
	char	**argv;
	char	*cmd_path;
	int		i;

	close(fd[0]);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	argv = ft_split(cmd1, NULL, 0, ' ');
	cmd_path = ft_find_command(argv[0], path_dirs);
	i = -1;
	// while (path_dirs[++i])
	// 	free (path_dirs);
	// free (path_dirs);
	close (infile_fd);	
	execve(cmd_path, argv, NULL);
	perror("execve");
	exit(EXECVE_ERROR);
}

void	ft_second_command(char *cmd2, int outfile_fd, char **path_dirs, int fd[])
{
	char	**argv;
	char	*cmd_path;
	int		i;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close (outfile_fd);
	close(fd[0]);
	argv = ft_split(cmd2, NULL, 0, ' ');
	cmd_path = ft_find_command(argv[0], path_dirs);
	i = -1;
	while (path_dirs[++i])
		free (path_dirs);
	free (path_dirs);
	close(outfile_fd);	
	execve(cmd_path, argv, NULL);
	perror("execve");
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
		exit (ARGUMENT_ERROR);
	}
	path_dirs = ft_get_path(env);
	if (!ft_check_access(av[1]))
	{
		perror("access");
		exit (ACCESS_ERROR);
	}
	infile_fd = open(av[1], O_RDONLY);
	if (infile_fd < 0)
	{
		perror("open");
		exit (OPEN_ERROR);
	}
	pipe_check = pipe(fd);
	if (pipe_check < 0)
	{
		perror("pipe");
		exit (PIPE_ERROR);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit (FORK_ERROR);
	}
	if (pid == 0)
		ft_first_command(av[2], infile_fd, path_dirs, fd);
	else
	{
		outfile_fd = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (outfile_fd < 0)
		{
			perror("open");
			exit (OPEN_ERROR);
		}
		wait(NULL);
		ft_second_command(av[3], outfile_fd, path_dirs, fd);
		close(outfile_fd);
	}
}

// check if any of the arguments are not empty strings or if the commands are correct

// check if the flags for the commands are together with '-' sign