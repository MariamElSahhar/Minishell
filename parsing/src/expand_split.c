/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:06:07 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/27 18:34:26 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	comb_quote_len(char *str)
{
	int		i;
	int		len;
	char	quote;
	int		open;

	i = 0;
	len = 0;
	if (str[0] && str[i] == '-')
	{
		i++;
		len++;
	}
	open = 0;
	while (str[i] && is_quote(str[i]))
	{
		if (is_quote(str[i]))
		{
			quote = str[i];
			open = 1;
			i++;
		}
		while (str[i] && (!open || (open && str[i] != quote)))
		{
			len++;
			i++;
		}
		if (str[i] == quote)
			i++;
	}
	return (len);
}

char	*comb_quote_str(t_word *word, int len)
{
	char	*comb;
	int		i;
	int		j;
	char	quote;
	int		open;

	comb = (char *)ft_calloc(len + 1, sizeof(char));
	if (!comb)
		return (0);
	i = 0;
	j = 0;
	if (word->cont[0] && word->cont[i] == '-')
	{
		comb[j] = '-';
		i++;
		j++;
	}
	open = 0;
	while (word->cont[i])
	{
		if (is_quote(word->cont[i]))
		{
			quote = word->cont[i];
			open = 1;
			i++;
		}
		while (word->cont[i] && (!open || (open && word->cont[i] != quote)))
		{
			comb[j] = word->cont[i];
			i++;
			j++;
		}
		if (word->cont[i] == quote)
			i++;
	}
	return (comb);
}

int	expand_quote(t_word *word)
{
	int		len;
	char	*comb;

	if (ft_strlen(word->cont) == 2)
		return (0);
	len = comb_quote_len(word->cont);
	comb = comb_quote_str(word, len);
	if (!comb)
		return (0);
	free(word->cont);
	word->cont = comb;
	return (1);
}

int	expand_split(t_split *split)
{
	t_word	*ptr;

	ptr = split->first;
	while (ptr)
	{
		if (ptr->type == QUOTE && !(ptr->prev && ptr->prev->type == REDIR))
		{
			expand_quote(ptr); //handle errors
			if (ptr == split->first || (ptr->prev && ptr->prev->type == PIPE))
				ptr->type = CMD;
			else if (ptr->prev && ptr->prev->type == REDIR)
				ptr->type = PATH;
			else
				ptr->type = FLAG;
		}
		else if (ptr->type == FLAG)
			expand_quote(ptr);
		ptr = ptr->next;
	}
	return (1);
}
