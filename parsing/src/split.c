/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:39:14 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/14 15:28:47 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

static int	in_quotes(int *i, char *input)
{
	int	quote;

	quote = input[*i];
	(*i) = (*i) + 1;
	while (input[*i] && input[*i] != quote)
		(*i) = (*i) + 1;
	if (input[*i] && input[*i] == quote)
	{
		(*i) = (*i) + 1;
		return (0);
	}
	return (1);
}

static int	count_commands(char *input)
{
	int		i;
	int		open;
	int		count;

	i = 0;
	count = 1;
	open = 0;
	while (input && input[i])
	{
		while (input[i] && !is_quote(input[i]) && input[i] != '|')
			i++;
		if (input[i] && is_quote(input[i]))
			open = in_quotes(&i, input);
		while (input[i] && !is_quote(input[i]) && input[i] != '|')
			i++;
		if (input[i] && input[i] == '|' && !open && !is_quote(input[i]))
		{
			count++;
			i++;
		}
	}
	return (count);
}


/* static void	init_word(char *d, char *s, int start)
{
	int	i;

	i = 0;
	while (s[start + i] && !is_space(s[start + i]))
	{
		d[i] = s[start + i];
		i++;
	}
	d[i] = '\0';
}

static void	init_arr(char **arr, char *s)
{
	int	i;
	int	j;
	int	word_size;

	i = 0;
	j = 0;
	while (s[i])
	{
		word_size = 0;
		while (s[i] && is_space(s[i]))
			i++;
		if (s[i] && !is_space(s[i]))
		{
			while (s[i] && !is_space(s[i]))
			{
				i++;
				word_size++;
			}
			arr[j] = (char *) malloc(word_size + 1);
			init_word(arr[j], s, i - word_size);
			j++;
		}
	}
}
 */
char	**split_input(char *input)
{
	int		num_commands;
	char	**commands_str;

	num_commands = count_commands(input);
	printf("%i commands\n", num_commands);
	commands_str = (char **)malloc(sizeof(char *) * (num_commands + 1));
	if (!commands_str)
		return (0);
	return (0);
	// init_arr(arr, (char *) s);
	// arr[num_commands] = 0;
	// return (arr);
}
