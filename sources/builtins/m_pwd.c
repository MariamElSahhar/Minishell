/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:43:03 by szerisen          #+#    #+#             */
/*   Updated: 2023/07/13 15:46:21 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
It will just display utils->pwd in stadard out fileno
*/
int	m_pwd(t_utils *utils, t_cmds *cmds)
{
	(void) cmds;
	if (utils->pwd)
		ft_putendl_fd(utils->pwd, STDOUT_FILENO);
	else
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
