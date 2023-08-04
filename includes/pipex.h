/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:46:02 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/03 17:03:44 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef LIMIT_ARGS
#  define LIMIT_ARGS 5
# endif

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "libft/libft.h"

// errors
# define ARGUMENT_ERROR  1
# define ACCESS_ERROR    2
# define OPEN_ERROR      1
# define PIPE_ERROR      4
# define FORK_ERROR      5
# define EXECVE_ERROR    126
# define CMD_NOT_FOUND   127

// directions
# define INFILE_TO_CMD   7
# define CMD_TO_OUTFILE  8
# define CMD_TO_CMD		 9

typedef struct s_store
{
	int		infile_fd;
	int		outfile_fd;
	int		fd[2];
	int		dup_fd[2];
	int		status;
	int		*pid;
	int		p_fd;
	char	**path_dirs;
	char	**cmd_av;
	char	*cmd_path;
	int		ac;
	char	**av;
	char	**env;
}				t_store;

/* path handling */
char	**ft_get_path(char *env[]);
char	*ft_find_path(char *env[], char *path);

/* command handling */
char	*ft_find_command(char *cmd, char **path_dirs);
char	*ft_strjoin_slash(char *src, char *dest);

/* multipipes */
void	ft_multipipes(t_store *store, int i, int j, int mode);
void	ft_exec_cmd(char *cmd, t_store *store, int flag, int hd_flag);
void	ft_open_and_redirect(t_store *store, int flag, int hd_flag);
void	ft_wait_and_free(t_store *store, int i, int mode);

/* here_doc */
void	ft_here_doc(t_store *store, char *line);

/* redirections */
void	ft_infile_to_cmd(t_store *store, int mode);
void	ft_cmd_to_outfile(t_store *store, int mode);
void	ft_cmd_to_cmd(t_store *store, int mode);

/* file opening */
void	ft_open_infile(t_store *store, int check);
void	ft_open_outfile(t_store *store, int check, bool hd_flag);

/* utils */
void	ft_initialize_store(t_store *store, int ac, char **av, char **env);
int		ft_check_access(char *path);
void	ft_free_and_close(t_store *store);
void	ft_free_array(char **arr);

#endif