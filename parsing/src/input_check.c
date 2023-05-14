/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:21:58 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/14 16:27:15 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

static int	empty_pipe(char *input)
{
	int	i;
	int	empty;

	i = 0;
	while (input && input[i])
	{
		empty = 1;
		while (input[i] && is_space(input[i]))
			i++;
		while (is_quote(input[i]))
			in_quotes(&i, input);
		if (input[i] && !is_space(input[i]) && !is_quote(input[i]))
			empty = 0;
	}
	return (empty);
}

static int	invalid_pipe(char *input)
{
	if (!ft_strchr(input, '|'))
		return (0);
	if (!ft_strncmp(input, ft_strchr(input, '|'), ft_strlen(input))
		|| ft_strlen(ft_strrchr(input, '|')) == 1)
		return (1);
	if (empty_pipe(input))
		return (1);
	return (0);
}

static int	invalid_char(char *input, char c)
{
	char	**sep;
	int		i;

	if (!ft_strchr(input, c))
		return (0);
	if (!ft_strncmp(input, ft_strchr(input, c), ft_strlen(input))
		|| ft_strlen(ft_strrchr(input, c)) == 1)
		return (1);
	sep = ft_split(input, c);
	i = -1;
	while (sep && sep[++i])
	{
		if (!open_quotes(sep[i]))
			return (1);
	}
	return (0);
}

static int	invalid_redir(char *input)
{
	char	**split;
	int		invalid;
	int		i;

	if (ft_strlen(ft_strrchr(input, '>')) == 1
		|| ft_strlen(ft_strrchr(input, '<')) == 1)
		return (1);
	invalid = 0;
	split = ft_split(input, '<');
	i = -1;
	while (split && split[++i])
	{
		if (is_empty(split[i]))
			invalid = 1;
	}
	free_double_ptr((void **) split);
	split = ft_split(input, '>');
	i = -1;
	while (split && split[++i])
	{
		if (is_empty(split[i]))
			invalid = 1;
	}
	free_double_ptr((void **) split);
	return (invalid);
}

int	check_input(char *input)
{
	if (open_quotes(input))
		printf("open quote\n");
	if (invalid_pipe(input))
		printf("invalid pipe\n");
	if (invalid_char(input, ';') || invalid_char(input, '\\'))
		printf("unexpected char ; or \\\n");
	if (invalid_redir(input))
		printf("invalid redirection\n");
	return (0);
}
