/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:46:02 by anshovah          #+#    #+#             */
/*   Updated: 2023/07/30 21:51:27 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "get_next_line/get_next_line.h"

// errors
# define ARGUMENT_ERROR  1
# define ACCESS_ERROR    2
# define OPEN_ERROR      3
# define PIPE_ERROR      4
# define FORK_ERROR      5
# define EXECVE_ERROR    6

// checking flags

// directions
# define INFILE_TO_CMD   7
# define CMD_TO_OUTFILE  8
# define CMD_TO_CMD		 9

// # define malloc(x) NULL

typedef	struct s_store
{
	int		infile_fd;
	int		outfile_fd;
	int		fd[2];
	int		p_fd;
	char	**path_dirs;
	int		ac;
	char	**av;
	char	**env;
}				t_store;

/* path handling */
char    **ft_get_path(char *env[]);
char    *ft_find_path(char *env[], char *path);

/* command handling */
char	*ft_find_command(char *cmd, char **path_dirs);
char	*ft_strjoin_slash(char *src, char *dest);

// multipipes
void	ft_multipipes(t_store *store, int i, int j);
void	ft_exec_cmd(char *cmd, t_store *store, int flag);
void	ft_manage_redirection(t_store *store, int flag);

// utils
int		ft_check_access(char *path);
void	ft_free_array(char **arr);

// libft utils
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	**ft_split(char *str, char *arr[], int count, char c);

#endif