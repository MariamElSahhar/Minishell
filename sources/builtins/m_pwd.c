/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:43:03 by szerisen          #+#    #+#             */
/*   Updated: 2023/05/30 20:11:49 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
It will just display utils->pwd in stadard out fileno
*/
int	m_pwd(t_utils *utils, t_cmds *cmds)
{
	(void) cmds;
	ft_putendl_fd(utils->pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
