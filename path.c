/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:44:37 by anshovah          #+#    #+#             */
/*   Updated: 2023/07/28 22:52:16 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    **ft_get_path(char *env[])
{
    char    *path;
    char    *abs_path;
    char    **path_dirs;
    int     skip;
    
    path = "PATH=";
    skip = 5;
    abs_path = ft_find_path(env, path);
    abs_path += skip;    
    path_dirs = ft_split(abs_path, NULL, 0, ':');
    if (!path_dirs)
        return (NULL);
    return (path_dirs);  
}
char    *ft_find_path(char *env[], char *path)
{
    int     i;
    
    i = -1;
    while (env[++i])
        if (!ft_strncmp(path, env[i], 5))
            return (env[i]);
    return (NULL);        
}
