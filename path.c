/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:44:37 by anshovah          #+#    #+#             */
/*   Updated: 2023/07/19 17:12:47 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    **ft_get_path(char *env[])
{
    char    *path;
    char    *ab_path;
    char    **path_dirs;
    int     skip;
    
    path = "PATH=";
    skip = 5;
    ab_path = ft_find_path(env, path);
    if (!ab_path)
        return (NULL);
    ab_path += skip;    
    path_dirs = ft_split(ab_path, NULL, 0, ':');
    return (path_dirs);  
}

char    *ft_find_path(char *env[], char *path)
{
    int     i;
    
    path = "PATH=";
    i = -1;
    while (env[++i])
        if (!ft_strncmp(path, env[i], 5))
            return (env[i]);
    return (NULL);        
}

//   int i = -1;
//     while (path_dirs[++i])
//         printf ("%s\n", path_dirs[i]);
//     i = -1;    
//     while (path_dirs[++i])
//         free(path_dirs[i]);
//     free (path_dirs); 