/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:29:44 by melsahha          #+#    #+#             */
/*   Updated: 2023/06/02 17:51:45 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	push_redir(t_cmds *cmd, t_word *ptr)
{
	t_redir	*r;
	t_redir	*redir;

	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (ptr->cont[0] == '<' && !ptr->cont[1])
		redir->type = INPUT;
	else if (ptr->cont[0] == '<' && !ptr->cont[1])
		redir->type = WRITE;
	else if (ptr->cont[0] == '<' && ptr->cont[1] == '<')
		redir->type = HEREDOC;
	else if (ptr->cont[0] == '>' && ptr->cont[1] == '>')
		redir->type = APPEND;
	ptr = ptr->next;
	if (ptr->type == PATH)
		redir->path = ptr->cont;
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
}

char	**init_args(t_word *ptr)
{
	t_word	*hold;
	int		count;
	char	**args;

	hold = ptr;
	count = 0;
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type == FLAG || ptr->type == ARG)
			count ++;
		ptr = ptr->next;
	}
	ptr = hold;
	args = (char **)ft_calloc(count + 1, sizeof(char *));
	count = 0;
	while (hold && hold->type != PIPE)
	{
		if (hold->type == FLAG || hold->type == ARG)
			args[count++] = hold->cont;
		hold = hold->next;
	}
	return (args);
}

void	last_in_redir(t_cmds *cmd)
{
	t_redir	*ptr;
	t_redir	*last;
	int		type;

	if (!cmd->redirections)
		return ;
	type = -1;
	ptr = cmd->redirections;
	while (ptr)
	{
		if (ptr->type == INPUT || ptr->type == HEREDOC)
		{
			type = ptr->type;
			ptr->type = IGNORE;
			last = ptr;
		}
		ptr = ptr->next;
	}
	if (type != -1)
		last->type = type;
}

void	last_out_redir(t_cmds *cmd)
{
	t_redir	*ptr;
	t_redir	*last;
	int		type;

	if (!cmd->redirections)
		return ;
	type = -1;
	ptr = cmd->redirections;
	while (ptr)
	{
		if (ptr->type == WRITE || ptr->type == APPEND)
		{
			type = ptr->type;
			ptr->type = OPEN;
			last = ptr;
		}
		ptr = ptr->next;
	}
	if (type != -1)
		last->type = type;
}

void	push_cmd(t_utils *utils, t_cmds *cmd)
{
	t_cmds	*ptr;

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

t_utils	*sort_tokens(t_split *split)
{
	t_utils	*utils;
	t_word	*ptr;
	t_cmds	*new_cmd;

	utils = (t_utils *)ft_calloc(1, sizeof(t_utils));
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
				push_redir(new_cmd, ptr);
			ptr = ptr->next;
		}
		if (ptr && ptr->type == PIPE)
			ptr = ptr->next;
		push_cmd(utils, new_cmd);
	}
	return (utils);
}
