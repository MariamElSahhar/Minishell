/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:51:59 by melsahha          #+#    #+#             */
/*   Updated: 2023/06/23 15:32:30 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// changes i to the index of the end of the flag
void	end_of_flag(char *input, int *i)
{
	while (input[(*i)] && !is_space(input[(*i)]) && !is_symbol(input[(*i)]))
	{
		while (input[(*i)] && !(is_space(input[(*i)])
				|| is_symbol(input[(*i)]) || is_quote(input[(*i)])))
			(*i)++;
		while (input[(*i)] && is_quote(input[(*i)]))
			skip_quotes(i, input);
	}
}

// finds the last input redirection
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

// finds the last output redirection
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

// sorts redirection types
void	sort_redir(t_word *ptr, t_redir *redir)
{
	if (ptr->cont[0] == '<' && !ptr->cont[1])
		redir->type = INPUT;
	else if (ptr->cont[0] == '>' && !ptr->cont[1])
		redir->type = WRITE;
	else if (ptr->cont[0] == '<' && ptr->cont[1] == '<')
		redir->type = HEREDOC;
	else if (ptr->cont[0] == '>' && ptr->cont[1] == '>')
		redir->type = APPEND;
}
