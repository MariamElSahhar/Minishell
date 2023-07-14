/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:56:31 by szerisen          #+#    #+#             */
/*   Updated: 2023/07/14 15:54:39 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "parsing.h"
# include "minishell.h"

// check_redirections
int				check_redirections(t_cmds *cmd);
int				handle_outfile(t_redir *redir);
int				handle_open(t_redir *redir);

// executor
int				prepare_executor(t_utils *utils);
int				executor(t_utils *utils);
int				pipe_wait(int *pid, int amount);

// handle_cmd
int				find_cmd(t_cmds *cmd, t_utils *utils);
void			handle_cmd(t_cmds *cmd, t_utils *utils);
void			dup_cmd(t_cmds *cmd, t_utils *utils,
					int end[2], int fd_in);
void			single_cmd(t_cmds *cmd, t_utils *utils);

// heredoc
int				send_heredoc(t_utils *utils, t_cmds *cmd);

//executor_utils
int				check_redir_helper(int type, t_redir *dir);

#endif
