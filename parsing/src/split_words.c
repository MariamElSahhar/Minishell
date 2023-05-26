/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:58:39 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/26 19:27:36 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	push_word(t_split *split, char *c, int type)
{
	t_word	*word;

	word = (t_word *)ft_calloc(1, sizeof(t_word));
	if (!word)
		return (0);
	word->type = type;
	word->cont = c;
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

int	add_redir(t_split *split, char *input, int *i)
{
	int	success;

	if (input[(*i) + 1] && input[(*i) + 1] == input[(*i)])
	{
		if (input[(*i)] == '>')
			success = push_word(split, ">>", REDIR);
		else
			success = push_word(split, "<<", REDIR);
		(*i) = (*i) + 2;
	}
	else
	{
		if (input[(*i)] == '>')
			success = push_word(split, ">", REDIR);
		else
			success = push_word(split, "<", REDIR);
		(*i) = (*i) + 1;
	}
	return (success);
}

int	add_quote(t_split *split, char *input, int *i)
{
	int		start;
	int		j;
	int		len;
	char	*str;

	start = (*i);
	skip_quotes(i, input);
	len = (*i) - start;
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (0);
	j = 0;
	while ((j + start) < (*i))
	{
		str[j] = input[start + j];

		j++;
	}
	if (!push_word(split, str, QUOTE))
		return (0);
	return (1);
}

int	add_flag(t_split *split, char *input, int *i)
{
	int		start;
	int		len;
	int		k;
	char	*str;

	start = (*i);
	(*i)++;
	while (input[(*i)] && !is_symbol(input[(*i)]))
		(*i)++;
	if (is_quote(input[(*i)]))
		skip_quotes(i, input);
	len = (*i) - start;
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (0);
	k = 0;
	while ((start + k) < (*i))
	{
		str[k] = input[start + k];
		k++;
	}
	if(!push_word(split, str, FLAG))
		return (0);
	return (1);
}

int	add_str(t_split *split, char *input, int *i)
{	int		start;
	int		len;
	int		k;
	char	*str;

	start = (*i);
	while (input[(*i)] && !is_symbol(input[(*i)]))
		(*i)++;
	len = (*i) - start;
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (0);
	k = 0;
	while ((start + k) < (*i))
	{
		str[k] = input[start + k];
		k++;
	}
	if(!push_word(split, str, STR))
		return (0);
	return (1);
}

int	define_word(char *input, int *i, t_split *split)
{
	int	success;
	if (input[(*i)] == '|')
	{
		success = push_word(split, "|", PIPE);
		(*i)++;
	}
	else if (input[(*i)] == '>' || input[(*i)] == '<')
		success = add_redir(split, input, i);
	else if (is_quote(input[(*i)]))
		success = add_quote(split, input, i);
	else if (input[(*i)] == '-')
		success = add_flag(split, input, i);
	else
		success = add_str(split, input, i);
	if (!success)
		return (0);
	printf("%i: %s\n", split->cmds, split->last->cont);
	return (1);
}

void	free_split(t_split *split)
{
	t_word	*del;
	t_word	*ptr;

	ptr = split->first;
	while (ptr)
	{
		del = ptr;
		ptr = ptr->next;
		// free(del->cont);
		free(del);
	}
	free(split);
}

t_split	*split_input(char *input)
{
	t_split	*split;
	int		i;

	split = (t_split *)ft_calloc(1, sizeof(t_split));
	split->cmds = 0;
	split->first = 0;
	split->last = 0;
	if (!split || !input)
		return (0);
	i = 0;
	while (input[i])
	{
		skip_space(input, &i);
		if (input[i])
		{
			if (!define_word(input, &i, split))
			{
				free_split(split);
				return (0);
			}
		}
	}
	return (split);
}
