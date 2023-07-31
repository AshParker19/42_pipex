/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:45:47 by anshovah          #+#    #+#             */
/*   Updated: 2023/07/31 21:18:08 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_multipipes_hd(t_store *store, int i, int j)
{
	store->pid = malloc((store->ac - 3) * sizeof(int));
	if (!store->pid)
		return ;
	while (i < store->ac - 4)
	{
		if (j < store->ac - 2)
			pipe(store->fd);
		store->pid[i] = fork();
		if (store->pid[i] == 0) //FIXME:redirection for here_doc
		{
			if (j == 3)
			{
				printf ("HERE\n");
				ft_exec_cmd(store->av[3], store, INFILE_TO_CMD);
			}
			else if (j == store->ac - 2)
			{
				printf ("THERE\n");
				ft_exec_cmd(store->av[store->ac - 2], store, CMD_TO_OUTFILE);
			}
			else
			{
				printf ("SOMEWHERE ELSE\n");
				ft_exec_cmd(store->av[j], store, CMD_TO_CMD);		
			}
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
	while (++i < store->ac - 4)
		waitpid(store->pid[i], NULL, 0);
	free (store->pid);	
	ft_free_array(store->path_dirs);
}

void	ft_here_doc(t_store *store)
{
	char	*line = NULL;
	
	while (1)
	{
		if (line)
			free (line);
		line = get_next_line(STDIN_FILENO);
		if (!(ft_strncmp(line, store->av[2], ft_strlen(store->av[2]))))
		{
			free (line);
			break;					
		}
		write(store->infile_fd, line, ft_strlen(line));
	}
	ft_multipipes_hd(store, 0, 3);
}

void	ft_initialize_store(t_store *store, int ac, char **av, char **env, int flag)
{
	if (flag == 1)
	{
		store->infile_fd = open(av[1], O_RDONLY);
		store->outfile_fd = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	}
	else if (flag == 2)
	{
		store->infile_fd = open("here_doc_buff", O_RDWR | O_CREAT , 0666);
		store->outfile_fd = open(av[ac - 1], O_RDWR | O_CREAT | O_APPEND, 0666);
	}
	store->path_dirs = ft_get_path(env);
	store->ac = ac;
	store->av = av;
	store->env = env;
}

int	main(int ac, char *av[], char *env[]) // TODO: error checking
{
	t_store	store;
	// TODO:figure out the way to initialize fds for different ways
	// if (ac < 5 || !*av[1])
	// {
	// 	write(2, "Wrong arguments!\n", 18);
	// 	exit (ARGUMENT_ERROR);
	// }
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		ft_initialize_store(&store, ac, av, env, 2); //ft_multipipes(&store, 0, 3, 4);
		ft_here_doc(&store);
		unlink("here_doc_buff");
	}
	else
	{
		ft_initialize_store(&store, ac, av, env, 1);
		ft_multipipes(&store, 0, 2);
	}
}
// check if any of the arguments are not empty strings or if the commands are correct

// check if the flags for the commands are together with '-' sign