/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:30:55 by anshovah          #+#    #+#             */
/*   Updated: 2023/07/31 20:57:15 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_multipipes(t_store *store, int i, int j)
{
	store->pid = malloc((store->ac - 3) * sizeof(int));
	if (!store->pid)
		return ;
	while (i < store->ac - 3)
	{
		if (j < store->ac - 2)
			pipe(store->fd);
		store->pid[i] = fork();
		if (store->pid[i] == 0)
		{
			if (j == 2)
				ft_exec_cmd(store->av[2], store, INFILE_TO_CMD);
			else if (j == store->ac - 2)
				ft_exec_cmd(store->av[store->ac - 2], store, CMD_TO_OUTFILE);
			else
				ft_exec_cmd(store->av[j], store, CMD_TO_CMD);		
		}
		if (i > 0)
			close(store->p_fd);
		if (i == store->ac - 4)
			close(store->fd[0]);
		close(store->fd[1]);
		i++;	
		j++;
		store->p_fd = store->fd[0];
	}
	close(store->infile_fd);
	close(store->outfile_fd);
	i = -1;
	while (++i < store->ac - 3)
		waitpid(store->pid[i], NULL, 0);
	free (store->pid);	
	ft_free_array(store->path_dirs);
}

void	ft_exec_cmd(char *cmd, t_store *store, int flag)
{
	char	**argv;
	char	*cmd_path;
	char	*info;
	int		fd2[2];

	argv = ft_split(cmd, ' ');
	cmd_path = ft_find_command(argv[0], store->path_dirs);
	ft_manage_redirection(store, flag, 0);
	if (cmd_path)
	{
		execve(cmd_path, argv, store->env);
		perror("execve");
	}
	else
		ft_printf("command not found: '%s'\n", argv[0]);
	close(store->s_fd1);
	close(store->s_fd2);
	close(store->outfile_fd);
	free (cmd_path);
	free (store->pid);
	ft_free_array(store->path_dirs);
	ft_free_array(argv);
	exit(EXECVE_ERROR);
}

void	ft_manage_redirection(t_store *store, int flag, int check)
{	
	if (flag == INFILE_TO_CMD)
	{
		if (store->infile_fd == -1)
		{
			close(store->outfile_fd);
			close(store->fd[0]);
			close(store->fd[1]);
			ft_free_array(store->path_dirs);
			exit(127);
		}
		close(store->fd[0]);
		check = dup2(store->infile_fd, STDIN_FILENO);
		store->s_fd1 = check;
		close(store->infile_fd);
		check = dup2(store->fd[1], STDOUT_FILENO);
		store->s_fd2 = check;
		close(store->fd[1]);
	}
	else if (flag == CMD_TO_OUTFILE)
	{
		if (store->outfile_fd == -1)
		{
			close(store->infile_fd);
			close(store->fd[0]);
			close(store->fd[1]);
			ft_free_array(store->path_dirs);
			exit(127);
		}
		check = dup2(store->p_fd, STDIN_FILENO);
		store->s_fd1 = check;
		close (store->p_fd);
		check = dup2(store->outfile_fd, STDOUT_FILENO);
		store->s_fd2 = check;
		close (store->outfile_fd);
	}
	else if (flag == CMD_TO_CMD)
	{
		check = dup2(store->p_fd, STDIN_FILENO);
		store->s_fd1 = check;
		close(store->p_fd);
		close(store->fd[0]);
		check = dup2(store->fd[1], STDOUT_FILENO);
		store->s_fd2 = check;
		close(store->fd[1]);
	}
}
