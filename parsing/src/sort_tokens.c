/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:29:44 by melsahha          #+#    #+#             */
/*   Updated: 2023/06/01 20:58:50 by melsahha         ###   ########.fr       */
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
	cmd->num_output++;
}

char	**init_args(t_split *split)
{
	t_word	*ptr;
	int		count;
	char	**args;

	count = 0;
	ptr = split->first;
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type == FLAG || ptr->type == ARG)
			count ++;
		ptr = ptr->next;
	}
	args = (char **)ft_calloc(count + 1, sizeof(char *));
	count = 0;
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type == FLAG || ptr->type == ARG)
			args[count++] = ptr->cont;
		ptr = ptr->next;
	}
	return (args);
}

t_utils	*sort_tokens(t_split *split)
{
	t_utils	*utils;
	t_word	*ptr;
	t_cmds	*new_cmd;
	int		i;

	utils = (t_utils *)ft_calloc(1, sizeof(t_utils));
	ptr = split->first;
	while (ptr)
	{
		new_cmd = (t_cmds *)ft_calloc(1, sizeof(t_cmds));
		new_cmd->args = init_args(split);
		i = 0;
		while (ptr && ptr->type != PIPE)
		{
			if (ptr->type == CMD)
				new_cmd->command = ptr->cont;
			else if (ptr->type == FLAG || ptr->type == ARG)
				new_cmd->args = init_args(split);
			else if (ptr->type == REDIR)
				push_redir(new_cmd, ptr);
			ptr = ptr->next;
		}
		if (ptr && ptr->type == PIPE)
			ptr = ptr->next;
	}
	return (utils);
}
