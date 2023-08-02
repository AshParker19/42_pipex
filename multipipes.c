/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:30:55 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/02 21:38:10 by anshovah         ###   ########.fr       */
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
				ft_exec_cmd(store->av[2], store, INFILE_TO_CMD, 0);
			else if (j == store->ac - 2)
				ft_exec_cmd(store->av[store->ac - 2], store, CMD_TO_OUTFILE, 0);
			else
				ft_exec_cmd(store->av[j], store, CMD_TO_CMD, 0);		
		}
		if (i > 0)
			close(store->p_fd);
		close(store->fd[1]);
		i++;	
		j++;
		store->p_fd = store->fd[0];
	}
	i = -1;
	while (++i < store->ac - 3)
		waitpid(store->pid[i], &store->status, 0);
	free (store->pid);	
	ft_free_array(store->path_dirs);
}

void	ft_exec_cmd(char *cmd, t_store *store, int flag, int hd_flag)
{
	char	**argv;
	char	*cmd_path;

	ft_open_and_redirect(store, flag, hd_flag);
	argv = ft_split(cmd, ' ');
	cmd_path = NULL;
	if (argv[0])
		cmd_path = ft_find_command(argv[0], store->path_dirs);
	if (cmd_path)
	{
		execve(cmd_path, argv, store->env);
		perror("execve");
	}
	else
	{
		ft_putstr_fd("command not found: ", 2);
		if (!argv[0])
			ft_putendl_fd("''", 2);
		else
			ft_putendl_fd(argv[0], 2);
	}
	close(store->dup_fd[0]);
	close(store->dup_fd[1]);
	if (store->outfile_fd != -1)
		close(store->outfile_fd);
	if (store->infile_fd != -1)	
		close(store->infile_fd);
	free (cmd_path);
	free (store->pid);
	ft_free_array(store->path_dirs);
	ft_free_array(argv);
	exit(EXECVE_ERROR);
}

// FIXME: CHECK DUP2 RETURN
void	ft_open_and_redirect(t_store *store, int flag, int hd_flag)
{	
	int check;
	
	if (flag == INFILE_TO_CMD)
	{
		if (!hd_flag)
		{
			check = store->infile_fd = open(store->av[1], O_RDONLY);
			if (check < 0)
			{
				perror("open");
				ft_free_array(store->path_dirs);
				free(store->pid);
				close(store->fd[0]);
				close(store->fd[1]);
				exit(OPEN_ERROR);
			}
		}
		close(store->fd[0]);
		store->dup_fd[0] = dup2(store->infile_fd, STDIN_FILENO);
		store->dup_fd[1] = dup2(store->fd[1], STDOUT_FILENO);
		close(store->fd[1]);
	}
	else if (flag == CMD_TO_OUTFILE)
	{
		if (!hd_flag)
		{
			check = store->outfile_fd = open(store->av[store->ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
			if (check < 0)
			{
				perror("open");
				ft_free_array(store->path_dirs);
				free(store->pid);
				close(store->fd[0]);
				close(store->fd[1]);
				exit(OPEN_ERROR);
			}
		}
		else
		{
			check = store->outfile_fd = open(store->av[store->ac - 1], O_RDWR | O_CREAT | O_APPEND, 0666);
			if (check < 0)
			{
				perror("open");
				close(store->infile_fd);
				ft_free_array(store->path_dirs);
				free(store->pid);
				close(store->fd[0]);
				close(store->fd[1]);
				exit(OPEN_ERROR);
			}
		}
		store->dup_fd[0] = dup2(store->p_fd, STDIN_FILENO);
		close (store->p_fd);
		store->dup_fd[1] = dup2(store->outfile_fd, STDOUT_FILENO);
		close (store->outfile_fd);
	}
	else if (flag == CMD_TO_CMD)
	{
		store->dup_fd[0] = dup2(store->p_fd, STDIN_FILENO);
		close(store->p_fd);
		close(store->fd[0]);
		store->dup_fd[1] = dup2(store->fd[1], STDOUT_FILENO);
		close(store->fd[1]);
	}
}
