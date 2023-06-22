/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:29:44 by melsahha          #+#    #+#             */
/*   Updated: 2023/06/22 12:10:32 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

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

// pushed command to list
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

// sorts tokens to list of commands
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
				new_cmd = push_redir(new_cmd, ptr);
			ptr = ptr->next;
		}
		if (!new_cmd)
			return (0);
		if (ptr && ptr->type == PIPE)
			ptr = ptr->next;
		push_cmd(utils, new_cmd);
	}
	return (utils);
}
