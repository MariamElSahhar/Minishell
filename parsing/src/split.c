/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:39:14 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/10 19:28:56 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

static int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static int	count_words(char *s)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (s[i] && !is_space(s[i]))
			res++;
		while (s[i] && !is_space(s[i]))
			i++;
	}
	return (res);
}

static void	init_word(char *d, char *s, int start)
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

char	**split_input(char const *s)
{
	int		num_words;
	char	**arr;

	num_words = count_words((char *) s);
	arr = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (!arr)
		return (0);
	init_arr(arr, (char *) s);
	arr[num_words] = 0;
	return (arr);
}
