/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:21:58 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/12 09:04:54 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

static int	is_empty(char *split)
{
	int	j;
	int	empty;

	j = 0;
	empty = 1;
	if (open_quotes(split))
		return (0);
	while (empty && split[j])
	{
		while (is_space(split[j]) || is_quote(split[j]))
			j++;
		if (split[j] && !is_space(split[j]) && !is_quote(split[j]))
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
		if (is_empty(piped[i]))
		{
			free_double_ptr((void **) piped);
			return (1);
		}
	}
	free_double_ptr((void **) piped);
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
