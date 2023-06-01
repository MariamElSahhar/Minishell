/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:58:39 by melsahha          #+#    #+#             */
/*   Updated: 2023/06/01 17:41:00 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

static int	add_redir(t_split *split, char *input, int *i)
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

static int	add_quote(t_split *split, char *input, int *i)
{
	int		start;
	int		j;
	int		len;
	char	*str;

	start = (*i);
	while (input[(*i)] && is_quote(input[(*i)]))
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
	printf("%s\n", str);
	if (!push_word(split, str, QUOTE))
		return (0);
	return (1);
}

static int	add_flag(t_split *split, char *input, int *i)
{
	int		start;
	int		len;
	int		k;
	char	*str;

	start = (*i);
	(*i)++;
	while (input[(*i)] && !is_space(input[(*i)] )&& !is_symbol(input[(*i)]))
	{
		while (input[(*i)] && !(is_space(input[(*i)]) || is_symbol(input[(*i)]) || is_quote(input[(*i)])))
			(*i)++;
		while (input[(*i)] && is_quote(input[(*i)]))
			skip_quotes(i, input);
	}
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

static int	add_str(t_split *split, char *input, int *i)
{	int		start;
	int		len;
	int		k;
	char	*str;

	start = (*i);
	while (input[(*i)] && !(is_symbol(input[(*i)]) || is_space(input[(*i)]) || is_quote(input[(*i)])))
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

	success = 0;
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
	return (success);
}
