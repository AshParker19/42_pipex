/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:20:06 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/03 16:55:27 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_open_infile(t_store *store, int check)
{
	check = open(store->av[1], O_RDONLY);
	if (check < 0)
	{
		perror("open");
		ft_free_and_close(store);
		exit(OPEN_ERROR);
	}
	store->infile_fd = check;
}

void	ft_open_outfile(t_store *store, int check, bool hd_flag)
{
	if (hd_flag == true)
		check = open(store->av[store->ac - 1],
				O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		check = open(store->av[store->ac - 1],
				O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (check < 0)
	{
		perror("open");
		ft_free_and_close(store);
		exit(OPEN_ERROR);
	}
	store->outfile_fd = check;
}

void	ft_infile_to_cmd(t_store *store, int mode)
{
	if (mode == 3)
		ft_open_infile(store, 0);
	close(store->fd[0]);
	store->dup_fd[0] = dup2(store->infile_fd, STDIN_FILENO);
	store->dup_fd[1] = dup2(store->fd[1], STDOUT_FILENO);
	close(store->fd[1]);
}

void	ft_cmd_to_outfile(t_store *store, int mode)
{
	if (mode == 4)
		ft_open_outfile(store, 0, true);
	else
		ft_open_outfile(store, 0, false);
	store->dup_fd[0] = dup2(store->p_fd, STDIN_FILENO);
	close (store->p_fd);
	store->dup_fd[1] = dup2(store->outfile_fd, STDOUT_FILENO);
	close (store->outfile_fd);
}

void	ft_cmd_to_cmd(t_store *store, int mode)
{
	store->dup_fd[0] = dup2(store->p_fd, STDIN_FILENO);
	close(store->p_fd);
	close(store->fd[0]);
	store->dup_fd[1] = dup2(store->fd[1], STDOUT_FILENO);
	close(store->fd[1]);
}
