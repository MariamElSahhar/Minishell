/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:49:12 by szerisen          #+#    #+#             */
/*   Updated: 2023/05/31 20:24:23 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <dirent.h>
# include "minishell.h"

//builtins
// void	change_path(t_utils *utils);

int	(*builtin_arr(char *str))(t_utils *utils, t_cmds *cmds);

int		m_echo(t_utils *utils, t_cmds *cmds);

int		m_cd(t_utils *utils, t_cmds *cmds);

int		m_pwd(t_utils *utils, t_cmds *cmds);

int		m_export(t_utils *utils, t_cmds *cmds);

int		m_unset(t_utils *utils, t_cmds *cmds);

int		m_env(t_utils *utils, t_cmds *cmds);

int		m_exit(t_utils *utils, t_cmds *cmds);

// int		mini_continue(t_utils *utils, t_cmds *cmds);

size_t	equal_sign(char *str);
int		check_valid_identifier(char c);

#endif