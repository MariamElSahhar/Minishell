/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:49:12 by szerisen          #+#    #+#             */
/*   Updated: 2023/05/15 17:45:52 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <dirent.h>
# include "minishell.h"

//builtins
// void	change_path(t_utils *tools);

int		echo(t_utils *utils, t_cmds *cmds);

// int		cd(t_utils *utils, t_cmds *cmds);

int		pwd(t_utils *utils, t_cmds *cmds);

// int		export(t_utils *utils, t_cmds *cmds);

// int		unset(t_utils *utils, t_cmds *cmds);

int		env(t_utils *utils, t_cmds *cmds);

// int		mini_exit(t_utils *utils, t_cmds *cmds);

// int		mini_continue(t_utils *utils, t_cmds *cmds);

// size_t	equal_sign(char *str);
// int		check_valid_identifier(char c);

#endif