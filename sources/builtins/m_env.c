/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:42:53 by szerisen          #+#    #+#             */
/*   Updated: 2023/07/06 17:29:54 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	m_env(t_utils *utils, t_cmds *cmds)
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
