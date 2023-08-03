/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:20:06 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/03 13:20:42 by anshovah         ###   ########.fr       */
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
		check = open(store->av[store->ac - 1], O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		check = open(store->av[store->ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (check < 0)
	{
		perror("open");
		ft_free_and_close(store);
		exit(OPEN_ERROR);
	}
	store->outfile_fd = check;
}
