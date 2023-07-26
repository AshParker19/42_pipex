/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:45:47 by anshovah          #+#    #+#             */
/*   Updated: 2023/07/26 16:14:03 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_first_command(char *cmd1, int infile_fd, char **path_dirs, int fd[], char *env[])
{
	char	**argv;
	char	*cmd_path;

	close(fd[0]);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	argv = ft_split(cmd1, NULL, 0, ' ');
	cmd_path = ft_find_command(argv[0], path_dirs);
	execve(cmd_path, argv, env);
	perror("execve");
	exit(EXECVE_ERROR);
}

void	ft_second_command(char *cmd2, int outfile_fd, char **path_dirs, int fd2[], char *env[])
{
	char	**argv;
	char	*cmd_path;
	int		i;

	close(fd2[1]);
	dup2(outfile_fd, STDOUT_FILENO);
	close (outfile_fd);
	dup2(fd2[0], STDIN_FILENO);
	close(fd2[0]);
	argv = ft_split(cmd2, NULL, 0, ' ');
	cmd_path = ft_find_command(argv[0], path_dirs);
	execve(cmd_path, argv, env);
	perror("execve");
	exit(EXECVE_ERROR);
}

int	main(int ac, char *av[], char *env[])
{
	char	**path_dirs;
	int		infile_fd;
	int		outfile_fd;
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_check;
	int		pipe_check2;

	if (ac != 5 || !*av[1])
	{
		write(2, "Wrong arguments!\n", 18);
		exit (ARGUMENT_ERROR);
	}
	if (!ft_check_access(av[1]))
	{
		perror("access");
		exit (ACCESS_ERROR);
	}
	pipe_check = pipe(fd);
	if (pipe_check < 0)
	{
		perror("pipe");
		exit (PIPE_ERROR);
	}
	path_dirs = ft_get_path(env);
	if (!path_dirs)
		exit (1);
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork");
		exit (FORK_ERROR);
	}
	if (pid1 == 0)
	{
		infile_fd = open(av[1], O_RDONLY);
		ft_first_command(av[2], infile_fd, path_dirs, fd, env);
	}
	pid2 = fork();
	if (pid2 < 0)
	{
		perror("fork");
		exit (FORK_ERROR);
	}
	if (pid2 == 0)
	{
		outfile_fd = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
		ft_second_command(av[3], outfile_fd, path_dirs, fd, env);
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
	ft_free_array(path_dirs);
}

// check if any of the arguments are not empty strings or if the commands are correct

// check if the flags for the commands are together with '-' sign