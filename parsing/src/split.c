/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:39:14 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/12 14:44:56 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

static int	count_commands(char *input)
{
	int		i;
	int		open;
	int		count;
	int		quote;

	i = 0;
	count = 0;
	while (input && input[i])
	{
		open = 0;
		while (input[i] && !is_quote(input[i]) && input[i] != '|')
			i++;
		if (is_quote(input[i]))
		{
			open = 1;
			quote = input[i];
			i++;
		}
		while (input[i] && !is_quote(input[i]) && input[i] != '|')
			i++;
		if (input[i] == quote)
		{
			open = 0;
			i++;
		}
		while (input[i] && !is_quote(input[i]) && input[i] != '|')
			i++;
		if (input[i] == '|' && !open)
		{
			count++;
			i++;
		}
		while (input[i] && !is_quote(input[i]) && input[i] != '|')
			i++;
	}

	return (count);
}


/* static int	count_commands(char *s)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		while (s[i] && s[i] != '|')
			i++;
		if (s[i] && s[i] == '|')
		{
			count++;
			i++;
		}
		while (s[i] && s[i] != '|')
			i++;
	}
	if (!count)
		return (1);
	return (count);
} */

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
	// char	**arr;

	num_commands = count_commands(input);
	printf("%i commands\n", num_commands);
	return (0);
	// arr = (char **)malloc(sizeof(char *) * (num_commands + 1));
	// if (!arr)
	// 	return (0);
	// init_arr(arr, (char *) s);
	// arr[num_commands] = 0;
	// return (arr);
}
