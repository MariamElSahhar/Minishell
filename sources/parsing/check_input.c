/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:21:58 by melsahha          #+#    #+#             */
/*   Updated: 2023/06/23 17:27:19 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// checks if char is present in string
static int	invalid_char(char *input, char c)
{
	int		i;

	if (!ft_strchr(input, c))
		return (0);
	i = 0;
	while (input[i])
	{
		skip_space(input, &i);
		if (input[i] && is_quote(input[i]))
			skip_quotes(&i, input);
		if (input[i] && input[i] == c)
			return (1);
		i++;
	}
	return (0);
}

//checks if this string has open/invalid quotes
static int	open_quotes(char *input)
{
	int	open;
	int	i;
	int	quote;

	open = 0;
	i = 0;
	while (input && input[i])
	{
		while (input[i] && !is_quote(input[i]))
			i++;
		if (is_quote(input[i]))
		{
			open = 1;
			quote = input[i];
			i++;
		}
		while (input[i] && input[i] != quote)
			i++;
		if (input[i] && input[i] == quote)
		{
			open = 0;
			i++;
		}
	}
	return (open);
}

// checks for basic input issues
int	check_input(char *input)
{
	if (open_quotes(input))
	{
		printf("open quote\n");
		ft_error(2, 0);
		return (0);
	}
	if (invalid_char(input, ';'))
	{
		parser_token_error(0, ERR_SEMICOL);
		return (0);
	}
	if (invalid_char(input, '\\'))
	{
		parser_token_error(0, ERR_BACKSLASH);
		return (0);
	}
	return (1);
}
