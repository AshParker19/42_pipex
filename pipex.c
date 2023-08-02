/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:45:47 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/02 16:31:33 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_multipipes_hd(t_store *store, int i, int j)
{
	store->pid = malloc((store->ac - 4) * sizeof(int));
	if (!store->pid)
		return ;
	while (i < store->ac - 4)
	{
		if (j < store->ac - 2)
			pipe(store->fd);
		store->pid[i] = fork();
		if (store->pid[i] == 0)
		{
			if (j == 3)
				ft_exec_cmd(store->av[3], store, INFILE_TO_CMD, 1);
			else if (j == store->ac - 2)
				ft_exec_cmd(store->av[store->ac - 2], store, CMD_TO_OUTFILE, 1);
			else
				ft_exec_cmd(store->av[j], store, CMD_TO_CMD, 1);		
		}
		if (i > 0)
			close(store->p_fd);
		close(store->fd[1]);
		i++;	
		j++;
		store->p_fd = store->fd[0];
	}
	close(store->infile_fd);
	i = -1;
	while (++i < store->ac - 4)
		waitpid(store->pid[i], &store->status, 0);
	free (store->pid);	
	ft_free_array(store->path_dirs);
}

void	ft_here_doc(t_store *store)
{
	char	*line = NULL;
	char	*delimiter;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(256);
	store->infile_fd = fd[1];
	delimiter = ft_strjoin(store->av[2], "\n");
	while (1)
	{
		if (line)
			free (line);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break;
		if (!(ft_strncmp(line, delimiter, ft_strlen(delimiter))))
		{
			free (line);
			break;					
		}
		write(store->infile_fd, line, ft_strlen(line));
	}
	close(store->infile_fd);
	free(delimiter);
	store->infile_fd = fd[0];
	ft_multipipes_hd(store, 0, 3);
}

void	ft_initialize_store(t_store *store, int ac, char **av, char **env, int flag)
{
	store->path_dirs = ft_get_path(env);
	store->ac = ac;
	store->av = av;
	store->env = env;
	store->infile_fd = -1;
	store->outfile_fd = -1;
}

int	main(int ac, char *av[], char *env[])
{
	t_store	store;
	
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		ft_initialize_store(&store, ac, av, env, 2);
		ft_here_doc(&store);
	}
	else
	{
		ft_initialize_store(&store, ac, av, env, 1);
		ft_multipipes(&store, 0, 2);
	}
	if (WIFEXITED(store.status))
		return (WEXITSTATUS(store.status));
	return (1);
}