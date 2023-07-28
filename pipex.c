/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:45:47 by anshovah          #+#    #+#             */
/*   Updated: 2023/07/28 22:48:45 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		dup2(store->p_fd, STDIN_FILENO);
		close(store->p_fd);
		dup2(store->outfile_fd, STDOUT_FILENO);
		close (store->outfile_fd);
	}
	else
	{
		dup2(store->p_fd, STDIN_FILENO);
		close(store->p_fd);
		close(store->fd[0]);
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
	int		j;
	int		pid;

	store.infile_fd = open(av[1], O_RDONLY);
	store.p_fd = store.infile_fd;
	store.outfile_fd = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	store.path_dirs = ft_get_path(env);
	store.env = env;
	j = 2;
	while (i < ac - 3)
	{
		if (j < ac - 2)
			pipe(store.fd);
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
		close(store.fd[1]);
		close(store.p_fd);
		store.p_fd = store.fd[0];
	}
	i = -1;
	while (++i < ac - 3)
		wait(NULL);
	ft_free_array(store.path_dirs);
}

	// outfile_fd = open(av[ac], O_RDWR, O_CREAT, O_TRUNC, 0666);


// check if any of the arguments are not empty strings or if the commands are correct

// check if the flags for the commands are together with '-' sign