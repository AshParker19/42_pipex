/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:45:47 by anshovah          #+#    #+#             */
/*   Updated: 2023/07/30 21:57:26 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_here_doc(t_store *store)
{
	int		hd_fd;
	char	*line = NULL;
	
	hd_fd = open("here_doc_buff", O_RDWR | O_CREAT , 0666);
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
		write(hd_fd, line, ft_strlen(line));
	}
}

void	ft_initialize_store(t_store *store, int ac, char **av, char **env)
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
		ft_initialize_store(&store, ac, av, env); //ft_multipipes(&store, 0, 3, 4);
		ft_here_doc(&store);
		unlink("here_doc_buff");
	}
	else
	{
		ft_initialize_store(&store, ac, av, env);
		ft_multipipes(&store, 0, 2);
	}
}
// check if any of the arguments are not empty strings or if the commands are correct

// check if the flags for the commands are together with '-' sign