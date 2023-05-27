/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:21:58 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/27 15:34:18 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

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

int	check_input(char *input)
{
	if (open_quotes(input))
	{
		printf("open quote\n");
		return (0);
	}
	if (invalid_char(input, ';') || invalid_char(input, '\\'))
	{

		printf("invalid character\n");
		return (0);
	}
	return (1);
}

