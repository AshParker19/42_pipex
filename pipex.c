/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:45:47 by anshovah          #+#    #+#             */
/*   Updated: 2023/07/27 22:03:49 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	ft_first_command(char *cmd1, int infile_fd, char **path_dirs, int fd[], char *env[])
// {
// 	char	**argv;
// 	char	*cmd_path;

// 	close(fd[0]);
// 	dup2(infile_fd, STDIN_FILENO);
// 	close(infile_fd);
// 	dup2(fd[1], STDOUT_FILENO);
// 	close(fd[1]);
// 	argv = ft_split(cmd1, NULL, 0, ' ');
// 	cmd_path = ft_find_command(argv[0], path_dirs);
// 	execve(cmd_path, argv, env);
// 	perror("execve");
// 	exit(EXECVE_ERROR);
// }

// void	ft_second_command(char *cmd2, int outfile_fd, char **path_dirs, int fd2[], char *env[])
// {
// 	char	**argv;
// 	char	*cmd_path;
// 	int		i;

// 	close(fd2[1]);
// 	dup2(outfile_fd, STDOUT_FILENO);
// 	close (outfile_fd);
// 	dup2(fnv);
// 	// ft_free_array(path_dirs);
// 	close(fd2[0]);
// 	argv = ft_split(cmd2, NULL, 0, ' ');
// 	cmd_path = ft_find_command(argv[0], path_dirs);
// 	execve(cmd_path, argv, env);
// 	perror("execve");
// 	exit(EXECVE_ERROR);
// }

void	ft_exec_cmd(char *cmd, t_store *store, int flag)
{
	char	**argv;
	char	*cmd_path;
	char	*info;
	int		fd2[2];

	argv = ft_split(cmd, NULL, 0, ' ');
	cmd_path = ft_find_command(argv[0], store->path_dirs);
	if (flag == 1)
	{
		close(store->fd[0]);
		dup2(store->infile_fd, STDIN_FILENO);
		close(store->infile_fd);
		dup2(store->fd[1], STDOUT_FILENO);
		close(store->fd[1]);
	}
	else if (flag == 2)
	{
		close(store->fd[1]);
		dup2(store->outfile_fd, STDOUT_FILENO);
		close (store->outfile_fd);
		dup2(store->fd[0], STDIN_FILENO);
		close(store->fd[0]);
	}
	else
	{
		close(store->fd[1]);
		dup2(store->fd[0], STDIN_FILENO);
		close(store->fd[0]);

		pipe(store->fd);
		dup2(store->fd[1], STDOUT_FILENO);
		close(store->fd[1]);
	}
	execve(cmd_path, argv, store->env);
	perror("execve");
	exit(EXECVE_ERROR);
}

int	main(int ac, char *av[], char *env[])
{
	t_store	store;
	
	int		i = 0;
	int		j = 0;
	int		pid;

	store.infile_fd = open(av[1], O_RDONLY);
	store.outfile_fd = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	store.path_dirs = ft_get_path(env);
	store.env = env;
	pipe(store.fd);
	j = 2;
	while (i < ac - 3)
	{
		pid = fork();
		if (pid == 0)
		{
			if (j == 2)
				ft_exec_cmd(av[2], &store, 1);
			else if (j == ac - 2)
				ft_exec_cmd(av[ac - 2], &store, 2);
			else
				ft_exec_cmd(av[j], &store, 0);		
		}
		i++;	
		j++;
	}
	close(store.fd[0]);
	close(store.fd[1]);
	i = 0;
	while (i < ac - 3)
	{
		wait(NULL);
		i++;
	}
	ft_free_array(store.path_dirs);
}

	// outfile_fd = open(av[ac], O_RDWR, O_CREAT, O_TRUNC, 0666);


// check if any of the arguments are not empty strings or if the commands are correct

// check if the flags for the commands are together with '-' sign