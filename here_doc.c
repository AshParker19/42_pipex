/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:36:58 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/03 16:50:46 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_here_doc(t_store *store, char *line)
{
	char	*delimiter;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(PIPE_ERROR);
	store->infile_fd = fd[1];
	delimiter = ft_strjoin(store->av[2], "\n");
	while (1)
	{
		if (line)
			free (line);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (!(ft_strncmp(line, delimiter, ft_strlen(delimiter))))
		{
			free (line);
			break ;
		}
		write(store->infile_fd, line, ft_strlen(line));
	}
	close(store->infile_fd);
	free(delimiter);
	store->infile_fd = fd[0];
	ft_multipipes(store, -1, 3, 4);
}
