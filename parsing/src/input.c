/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:21:58 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/11 17:12:23 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

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

static int	empty_pipe(char *piped)
{
	int	j;
	int	empty;

	j = 0;
	empty = 1;
	if (open_quotes(piped))
		return (0);
	while (empty && piped[j])
	{
		while (is_space(piped[j]) || is_quote(piped[j]))
			j++;
		if (piped[j] && !is_space(piped[j]) && !is_quote(piped[j]))
			empty = 0;
	}
	return (empty);
}

static int	invalid_pipe(char *input)
{
	char	**piped;
	int		i;

	if (!ft_strchr(input, '|'))
		return (0);
	if (!ft_strncmp(input, ft_strchr(input, '|'), ft_strlen(input))
		|| ft_strlen(ft_strrchr(input, '|')) == 1)
		return (1);
	piped = ft_split(input, '|');
	i = -1;
	while (piped && piped[++i])
	{
		if (empty_pipe(piped[i]))
			return (1);
	}
	return (0);
}

int	check_input(char *input)
{
	if (open_quotes(input))
		printf("open quote\n");
	else
		printf("closed quote\n");

	if (invalid_pipe(input))
		printf("invalid pipe\n");
	else
		printf("valid pipes\n");
	return (0);
}
