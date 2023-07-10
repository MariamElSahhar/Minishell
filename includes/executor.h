/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:56:31 by szerisen          #+#    #+#             */
/*   Updated: 2023/07/10 18:12:58 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "parsing.h"
# include "minishell.h"

// check_redirections
// int				check_outfile(t_lexer *redirections);
// int				check_infile(t_lexer *redirections);
// int				handle_redirections(t_cmds *cmd, t_utils *utils);
int				check_redirections(t_cmds *cmd);

// executor
int				executor(t_utils *utils);
t_cmds	*call_expander(t_utils *utils, t_cmds *cmd);
int				pipe_wait(int *pid, int amount);

// handle_cmd
int				find_cmd(t_cmds *cmd, t_utils *utils);
void			handle_cmd(t_cmds *cmd, t_utils *utils);
void			dup_cmd(t_cmds *cmd, t_utils *utils,
					int end[2], int fd_in);
void			single_cmd(t_cmds *cmd, t_utils *utils);

// heredoc
int				send_heredoc(t_utils *utils, t_cmds *cmd);

#endif
