/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:29:44 by melsahha          #+#    #+#             */
/*   Updated: 2023/06/23 19:24:22 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// adds redirection to list
t_cmds	*push_redir(t_cmds *cmd, t_word *ptr)
{
	t_redir	*r;
	t_redir	*redir;

	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (ptr->next->type == PATH)
		redir->path = ptr->next->cont;
	else
		return (0);
	sort_redir(ptr, redir);
	r = cmd->redirections;
	if (!r)
		cmd->redirections = redir;
	else
	{
		while (r->next)
			r = r->next;
		r->next = redir;
	}
	redir->prev = r;
	return (cmd);
}

// ints the argument list
char	**init_args(t_word *start)
{
	t_word	*ptr;
	int		count;
	char	**args;

	ptr = start;
	count = 0;
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type == FLAG || ptr->type == ARG)
			count ++;
		ptr = ptr->next;
	}
	ptr = start;
	args = (char **)ft_calloc(count + 2, sizeof(char *));
	count = 1;
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type == FLAG || ptr->type == ARG)
			args[count++] = ptr->cont;
		ptr = ptr->next;
	}
	return (args);
}

void	check_builtin(t_cmds *cmd)
{
	if (!ft_strncmp(cmd->command, "cd", ft_strlen(cmd->command)))
		cmd->builtin = &m_cd;
	else if (!ft_strncmp(cmd->command, "echo", ft_strlen(cmd->command)))
		cmd->builtin = &m_echo;
	else if (!ft_strncmp(cmd->command, "env", ft_strlen(cmd->command)))
		cmd->builtin = &m_env;
	else if (!ft_strncmp(cmd->command, "exit", ft_strlen(cmd->command)))
		cmd->builtin = &m_exit;
	else if (!ft_strncmp(cmd->command, "export", ft_strlen(cmd->command)))
		cmd->builtin = &m_export;
	else if (!ft_strncmp(cmd->command, "pwd", ft_strlen(cmd->command)))
		cmd->builtin = &m_pwd;
	else if (!ft_strncmp(cmd->command, "unset", ft_strlen(cmd->command)))
		cmd->builtin = &m_unset;
}

// pushed command to list
void	push_cmd(t_utils *utils, t_cmds *cmd)
{
	t_cmds	*ptr;

	check_builtin(cmd);
	last_in_redir(cmd);
	last_out_redir(cmd);
	ptr = utils->cmds;
	if (!ptr)
		utils->cmds = cmd;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = cmd;
		cmd->prev = ptr;
	}
}

// sorts tokens to list of commands
int	sort_tokens(t_split *split, t_utils *utils)
{
	t_word	*ptr;
	t_cmds	*new_cmd;

	ptr = split->first;
	while (ptr)
	{
		new_cmd = (t_cmds *)ft_calloc(1, sizeof(t_cmds));
		new_cmd->args = init_args(ptr);
		while (ptr && ptr->type != PIPE)
		{
			if (ptr->type == CMD)
				new_cmd->command = ptr->cont;
			else if (ptr->type == REDIR)
				new_cmd = push_redir(new_cmd, ptr);
			ptr = ptr->next;
		}
		if (!new_cmd)
			return (0);
		new_cmd->args[0] = new_cmd->command;
		push_cmd(utils, new_cmd);
		if (ptr && ptr->type == PIPE)
			ptr = ptr->next;
	}
	return (1);
}
