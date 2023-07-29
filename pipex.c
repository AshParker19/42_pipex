/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:45:47 by anshovah          #+#    #+#             */
/*   Updated: 2023/07/29 22:54:47 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_manage_redirection(t_store *store, int flag)
{
	if (flag == INFILE_TO_CMD)
	{
		close(store->fd[0]);
		dup2(store->infile_fd, STDIN_FILENO);
		close(store->infile_fd);
		dup2(store->fd[1], STDOUT_FILENO);
		close(store->fd[1]);
	}
	else if (flag == CMD_TO_OUTFILE)
	{
		dup2(store->p_fd, STDIN_FILENO);
		close(store->p_fd);
		dup2(store->outfile_fd, STDOUT_FILENO);
		close (store->outfile_fd);
	}
	else if (flag == CMD_TO_CMD)
	{
		dup2(store->p_fd, STDIN_FILENO);
		close(store->p_fd);
		close(store->fd[0]);
		dup2(store->fd[1], STDOUT_FILENO);
		close(store->fd[1]);
	}
}

void	ft_exec_cmd(char *cmd, t_store *store, int flag)
{
	char	**argv;
	char	*cmd_path;
	char	*info;
	int		fd2[2];

	argv = ft_split(cmd, NULL, 0, ' ');
	cmd_path = ft_find_command(argv[0], store->path_dirs);
	ft_manage_redirection(store, flag);
	execve(cmd_path, argv, store->env);
	perror("execve");
	free (cmd_path);
	ft_free_array(argv);
	exit(EXECVE_ERROR);
}

void	ft_multipipes(t_store *store, int i, int j)
{
	int	pid;
	
	while (i < store->ac - 3)
	{
		if (j < store->ac - 2)
			pipe(store->fd);
		pid = fork();
		if (pid == 0)
		{
			if (j == 2)
				ft_exec_cmd(store->av[2], store, INFILE_TO_CMD);
			else if (j == store->ac - 2)
				ft_exec_cmd(store->av[store->ac - 2], store, CMD_TO_OUTFILE);
			else
				ft_exec_cmd(store->av[j], store, CMD_TO_CMD);		
		}
		i++;	
		j++;
		close(store->fd[1]);
		close(store->p_fd);
		store->p_fd = store->fd[0];
	}
	i = -1;
	while (++i < store->ac - 3)
		wait(NULL);
	ft_free_array(store->path_dirs);
}

void	ft_here_doc(t_store *store)
{
	
}

void	ft_initialize_store(t_store *store, int ac, char **av, char **env)
{
	store->infile_fd = open(av[1], O_RDONLY);
	store->outfile_fd = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	store->path_dirs = ft_get_path(env);
	store->ac = ac;
	store->av = av;
	store->env = env;
}

int	main(int ac, char *av[], char *env[])
{
	t_store	store;
	
	if (ac < 5 || !*av[1])
	{
		write(2, "Wrong arguments!\n", 18);
		exit (ARGUMENT_ERROR);
	}
	ft_initialize_store(&store, ac, av, env);
	if (!ft_strncmp(av[1], "here_doc", 8))
		ft_here_doc(&store);
	else
		ft_multipipes(&store, 0, 2);	
}
// check if any of the arguments are not empty strings or if the commands are correct

// check if the flags for the commands are together with '-' sign