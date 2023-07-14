/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:49:03 by melsahha          #+#    #+#             */
/*   Updated: 2023/07/14 20:43:49 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// creates new word
t_word	*new_word(char *c, int type)
{
	t_word	*word;

	word = (t_word *)ft_calloc(1, sizeof(t_word));
	if (!word)
	{
		ft_error(1, 0);
		return (0);
	}
	word->type = type;
	word->cont = ft_strdup(c);
	return (word);
}

// pushes word to list
int	push_word(t_split *split, char *c, int type)
{
	t_word	*word;

	word = new_word(c, type);
	if (!word)
		return (0);
	word->index = split->cmds;
	word->next = 0;
	word->prev = split->last;
	if (split->cmds == 0)
		split->first = word;
	else
		split->last->next = word;
	split->last = word;
	split->cmds++;
	return (1);
}

// prints split list for visualization
void	print_split(t_split *split)
{
	t_word	*ptr;

	ptr = split->first;
	while (ptr)
	{
		printf("%i. ", ptr->index);
		printf("%s", ptr->cont);
		if (ptr->type == CMD)
			printf(" - CMD\n");
		else if (ptr->type == REDIR)
			printf(" - REDIR\n");
		else if (ptr->type == PATH)
			printf(" - PATH\n");
		else if (ptr->type == PIPE)
			printf(" - PIPE\n");
		else if (ptr->type == QUOTE)
			printf(" - QUOTE\n");
		else if (ptr->type == ARG)
			printf(" - ARG\n");
		else if (ptr->type == STR)
			printf(" - STR\n");
		ptr = ptr->next;
	}
}

char	*expand_env_quotes(t_word *word, int *i, t_utils *utils)
{
	if (word->cont[(*i)] == '\'')
		skip_quotes(i, word->cont);
	else if (word->cont[(*i)] == '\"')
	{
		(*i)++;
		while (word->cont[(*i)] && word->cont[(*i)] != '\"')
		{
			if (word->cont[(*i)] == '$')
			{
				if (word->cont[(*i) + 1] && word->cont[(*i) + 1] == '?')
					word->cont = expand_err(word->cont, i);
				else
					found_env(word->cont, i, word, utils);
				break ;
			}
			else
				(*i)++;
		}
		if (word->cont[(*i)] == '\"')
			(*i)++;
	}
	return (word->cont);
}
