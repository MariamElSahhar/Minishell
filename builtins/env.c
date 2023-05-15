/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:42:53 by szerisen          #+#    #+#             */
/*   Updated: 2023/05/15 17:45:45 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	mini_env(t_utils *utils, t_cmds *cmds)
{
	int		i;

	(void) cmds;
	i = 0;
	while (utils->envp[i])
	{
		ft_putendl_fd(utils->envp[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
