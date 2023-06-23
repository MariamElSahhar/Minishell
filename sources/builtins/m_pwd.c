/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:43:03 by szerisen          #+#    #+#             */
/*   Updated: 2023/06/23 16:30:34 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
It will just display utils->pwd in stadard out fileno
*/
int	m_pwd(t_utils *utils, t_cmds *cmds)
{
	(void) cmds;
	ft_putendl_fd(utils->pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
