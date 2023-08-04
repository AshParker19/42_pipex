/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:45:47 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/03 17:44:51 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char *av[], char *env[])
{
	t_store	store;

	if ((LIMIT_ARGS != -1 && ac != LIMIT_ARGS) || (ac < 5))
	{
		ft_putstr_fd("Wrong arguments!\n", 2);
		return (ARGUMENT_ERROR);
	}
	if (ft_strncmp(av[1], "here_doc", 9) == 0 && ac < 6)
	{
		ft_putstr_fd("Wrong arguments!\n", 2);
		return (ARGUMENT_ERROR);
	}
	ft_initialize_store(&store, ac, av, env);
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		ft_here_doc(&store, NULL);
	else
		ft_multipipes(&store, -1, 2, 3);
	if (WIFEXITED(store.status))
		return (WEXITSTATUS(store.status));
	return (1);
}
