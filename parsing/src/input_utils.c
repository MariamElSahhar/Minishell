/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:58:40 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/25 21:38:12 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

//frees double pointer
void	free_double_ptr(void **ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	if (ptr)
		free(ptr);
}

//checks if character is a space
int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

//checks if character is a quote
int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

//checks if character is a marker symbol
int	is_symbol(char c)
{
	if (is_space(c) || is_quote(c))
		return (1);
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

//if input[i] is a quote, we jump i to the input[i] character after the close of the quote
void	skip_quotes(int *i, char *input)
{
	int	quote;

	quote = input[*i];
	(*i) = (*i) + 1;
	while (input[*i] && input[*i] != quote)
		(*i) = (*i) + 1;
	if (input[*i] && input[*i] == quote)
		(*i) = (*i) + 1;
}
