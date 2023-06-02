/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:49:03 by melsahha          #+#    #+#             */
/*   Updated: 2023/06/02 17:46:11 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	replace_word(t_word *cmd_word, int index, t_split *split)
{
	int		i;
	t_word	*old_word;

	i = 0;
	old_word = split->first;
	while (i < index)
		old_word = old_word->next;
	cmd_word->index = index;
	cmd_word->prev = old_word->prev;
	cmd_word->next = old_word->next;
	if (cmd_word->next)
		cmd_word->next->prev = cmd_word;
	if (cmd_word->prev)
		cmd_word->prev->next = cmd_word;
	if (index == 0)
		split->first = cmd_word;
	if (index == split->cmds - 1)
		split->last = cmd_word;
	free(old_word->cont);
	free(old_word);
}

t_word	*new_word(char *c, int type)
{
	t_word	*word;

	word = (t_word *)ft_calloc(1, sizeof(t_word));
	if (!word)
		return (0);
	word->type = type;
	word->cont = c;
	return (word);
}

int	push_word(t_split *split, char *c, int type)
{
	t_word	*word;

	word = new_word(c, type);
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
		else if (ptr->type == FLAG)
			printf(" - FLAG\n");
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
