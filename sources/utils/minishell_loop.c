/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:08:09 by szerisen          #+#    #+#             */
/*   Updated: 2023/07/10 18:21:02 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	minishell_loop(t_utils *utils, char **envp);

/*
This function initializes the utils
 structure with default values and
 sets up the environment.
It sets various variables and flags
 in the utils structure to their initial values.
It calls the parse_envp function to
 parse the environment variables and
 store them in the utils structure.
It calls the init_signals function to
 set up signal handling for the minishell.
*/
int	implement_utils(t_utils *utils)
{
	utils->cmds = NULL;
	utils->reset = false;
	utils->pid = NULL;
	utils->heredoc = false;
	g_global.stop_heredoc = 0;
	g_global.in_cmd = 0;
	g_global.in_heredoc = 0;
	parse_envp(utils);
	return (1);
}
/*
The reset_utils function is called to reset
 the utils structure and restart the minishell
 loop if needed.
This function resets the utils structure and
restarts the minishell loop if needed.
It frees the memory allocated for the command
 list (cmdss), arguments (args), process IDs
 (pid), and paths (paths).
It calls the implement_utils function to
re-initialize the utils structure with
default values and set up the environment.
Finally, it calls the minishell_loop
function to restart the minishell loop.
*/

void	free_cmd(t_cmds *cmd)
{
	t_redir	*ptr;
	t_redir	*del;

	if (cmd->hd_file_name)
		free(cmd->hd_file_name);
	if (cmd->args)
		free_double_ptr((void **) cmd->args);
	ptr = cmd->redirections;
	while (ptr)
	{
		del = ptr;
		ptr = ptr->next;
		if (del->path)
			free(del->path);
		free(del);
	}
	free(cmd);
}

void	free_utils(t_utils *utils)
{
	t_cmds	*ptr;
	t_cmds	*del;

	ptr = utils->cmds;
	while (ptr)
	{
		del = ptr;
		ptr = ptr->next;
		free_cmd(del);
	}
	if (utils->input)
		free(utils->input);
	if (utils->pid)
		free(utils->pid);
	if (utils->pwd)
		free(utils->pwd);
	if (utils->old_pwd)
		free(utils->old_pwd);
	free_double_ptr((void **)utils->envp);
	free_double_ptr((void **)utils->paths);
}

int	reset_utils(t_utils *utils)
{
	free_utils(utils);
	utils->reset = true;
	return (1);
}

void	minishell_loop(t_utils *utils, char **envp)
{
	while (1)
	{
		utils->input = readline(READLINE_MSG);
		utils->envp = ft_arrdup(envp);
		find_pwd(utils);
		implement_utils(utils);
		if (!utils->input)
		{
			reset_utils(utils);
			rl_replace_line("exit", 0);
			exit(EXIT_SUCCESS);
		}
		else if (utils->input[0] == '\0')
		{
			reset_utils(utils);
			continue ;
		}
		add_history(utils->input);
		if (parse_input(utils))
			prepare_executor(utils);
		reset_utils(utils);
	}
}
