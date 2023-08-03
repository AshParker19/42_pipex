/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:30:55 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/03 13:24:06 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_multipipes(t_store *store, int i, int j, int hd_flag)
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
	ft_open_and_redirect(store, flag, hd_flag);
	store->cmd_av = ft_split(cmd, ' ');
	store->cmd_path = NULL;
	if (store->cmd_av[0])
		store->cmd_path = ft_find_command(store->cmd_av[0], store->path_dirs);
	if (store->cmd_path)
	{
		execve(store->cmd_path, store->cmd_av, store->env);
		perror("execve");
	}
	else
	{
		ft_putstr_fd("command not found: ", 2);
		if (!store->cmd_av[0])
			ft_putendl_fd("''", 2);
		else
			ft_putendl_fd(store->cmd_av[0], 2);
	}
	ft_free_and_close(store);
	exit(EXECVE_ERROR);
}

// FIXME: CHECK DUP2 RETURN
void	ft_open_and_redirect(t_store *store, int flag, int hd_flag)
{	
	int check;
	
	if (flag == INFILE_TO_CMD)
	{
		if (!hd_flag)
			ft_open_infile(store, 0);
		close(store->fd[0]);
		store->dup_fd[0] = dup2(store->infile_fd, STDIN_FILENO);
		store->dup_fd[1] = dup2(store->fd[1], STDOUT_FILENO);
		close(store->fd[1]);
	}
	else if (flag == CMD_TO_OUTFILE)
	{
		if (hd_flag)
			ft_open_outfile(store, 0, true);
		else
			ft_open_outfile(store, 0, false);			
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
