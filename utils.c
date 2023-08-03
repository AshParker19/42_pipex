/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:09:00 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/03 16:54:44 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_initialize_store(t_store *store, int ac, char **av, char **env)
{
	store->path_dirs = ft_get_path(env);
	store->ac = ac;
	store->av = av;
	store->env = env;
	store->infile_fd = -1;
	store->outfile_fd = -1;
	store->fd[0] = -1;
	store->fd[1] = -1;
	store->dup_fd[0] = -1;
	store->dup_fd[1] = -1;
	store->p_fd = -1;
	store->pid = NULL;
	store->cmd_av = NULL;
	store->cmd_path = NULL;
}

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

void	ft_free_and_close(t_store *store)
{
	if (store->infile_fd != -1)
		close(store->infile_fd);
	if (store->outfile_fd != -1)
		close(store->outfile_fd);
	if (store->fd[0] != -1)
		close(store->fd[0]);
	if (store->fd[1] != -1)
		close(store->fd[1]);
	if (store->dup_fd[0] != -1)
		close(store->dup_fd[0]);
	if (store->dup_fd[1] != -1)
		close(store->dup_fd[1]);
	if (store->p_fd != -1)
		close(store->p_fd);
	if (store->pid)
		free(store->pid);
	if (store->path_dirs)
		ft_free_array(store->path_dirs);
	if (store->cmd_av)
		ft_free_array(store->cmd_av);
	if (store->cmd_path)
		free(store->cmd_path);
}

void	ft_free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free (arr);
}
