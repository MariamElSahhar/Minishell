/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:06:07 by melsahha          #+#    #+#             */
/*   Updated: 2023/07/05 19:41:26 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// caculates length of string with combined quotes
int	comb_quote_len(char *str)
{
	int		i;
	size_t	len;

	len = ft_strlen(str);
	i = 0;
	while (str && str[i])
	{
		if (is_quote(str[i]))
		{
			skip_quotes(&i, str);
			len = len - 2;
		}
		while (str[i] && !is_quote(str[i]))
			i++;
	}
	return (len);
}

// returns the combined-quote string
char	*comb_quote_str(t_word *word, size_t len)
{
	char	*comb;
	int		i;
	int		j;
	char	quote;

	comb = (char *)ft_calloc(len + 1, sizeof(char));
	if (!comb)
		return (0);
	i = 0;
	j = 0;
	while (word->cont && word->cont[i])
	{
		if (is_quote(word->cont[i]))
		{
			quote = word->cont[i++];
			if (word->cont[i] == quote)
				i++;
			else
			{
				while (word->cont[i] && word->cont[i] != quote)
				{
					comb[j++] = word->cont[i++];
				}
				i++;
			}
		}
		while (word->cont[i] && !is_quote(word->cont[i]))
			comb[j++] = word->cont[i++];
	}
	return (comb);
}

// calls functions to combine quotes in words
int	expand_quote(t_word *word)
{
	size_t	len;
	char	*comb;

	if (!ft_strchr(word->cont, '\'') && !ft_strchr(word->cont, '\"'))
		return (0);
	len = comb_quote_len(word->cont);
	comb = comb_quote_str(word, len);
	if (!comb)
		return (0);
	free(word->cont);
	word->cont = comb;
	return (1);
}

// finds quotes, calls expander, and replaces with correct type
int	expand_split(t_split *split)
{
	t_word	*ptr;

	ptr = split->first;
	while (ptr)
	{
		if (ptr->type == QUOTE && !(ptr->prev && ptr->prev->type == REDIR))
		{
			expand_quote(ptr);
			if (ptr == split->first || (ptr->prev && ptr->prev->type == PIPE))
				ptr->type = CMD;
			else if (ptr->prev && ptr->prev->type == REDIR)
				ptr->type = PATH;
			else
				ptr->type = STR;
		}
		else
			expand_quote(ptr);
		ptr = ptr->next;
	}
	return (1);
}
