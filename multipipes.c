/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:30:55 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/03 16:52:11 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_multipipes(t_store *store, int i, int j, int mode)
{
	store->pid = malloc((store->ac - mode) * sizeof(int));
	if (!store->pid)
		return ;
	while (++i < store->ac - mode)
	{
		if (j < store->ac - 2)
			pipe(store->fd);
		store->pid[i] = fork();
		if (store->pid[i] == 0)
		{
			if (j == mode - 1)
				ft_exec_cmd(store->av[mode - 1], store, INFILE_TO_CMD, mode);
			else if (j == store->ac - 2)
				ft_exec_cmd(store->av[store->ac - 2], store,
					CMD_TO_OUTFILE, mode);
			else
				ft_exec_cmd(store->av[j], store, CMD_TO_CMD, mode);
		}
		if (i > 0)
			close(store->p_fd);
		close(store->fd[1]);
		j++;
		store->p_fd = store->fd[0];
	}
	ft_wait_and_free(store, -1, mode);
}

void	ft_wait_and_free(t_store *store, int i, int mode)
{
	if (mode == 4)
		close(store->infile_fd);
	while (++i < store->ac - mode)
		waitpid(store->pid[i], &store->status, 0);
	ft_free_and_close(store);
}

void	ft_exec_cmd(char *cmd, t_store *store, int flag, int mode)
{
	ft_open_and_redirect(store, flag, mode);
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
	if (store->cmd_path)
		exit(EXECVE_ERROR);
	else
		exit(CMD_NOT_FOUND);
}

void	ft_open_and_redirect(t_store *store, int flag, int mode)
{
	if (flag == INFILE_TO_CMD)
		ft_infile_to_cmd(store, mode);
	else if (flag == CMD_TO_OUTFILE)
		ft_cmd_to_outfile(store, mode);
	else if (flag == CMD_TO_CMD)
		ft_cmd_to_cmd(store, mode);
	if (store->dup_fd[0] == -1 || store->dup_fd[1] == -1)
	{
		ft_free_and_close(store);
		exit (PIPE_ERROR);
	}
}
