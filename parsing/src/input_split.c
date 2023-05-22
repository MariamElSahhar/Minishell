/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:58:39 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/22 17:15:38 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

char	**join_str(char **arr, char *str);
void	skip_quotes(char *input, int *i);
char	**split_input(char *input);

int	count_chunks(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input && input[i])
	{
		while(input[i] && is_space(input[i]))
			i++;
		if (input[i] && !is_space(input[i]))
			count++;
		if (input[i] && is_quote(input[i]))
			skip_quotes(&i, input);
		else if (input[i] && (input[i] == '|'
			|| input[i] == '>' || input[i] == '<'))
		while (input[i] && !is_space(input[i]))
			i++;
	}
}

char	**split_input(char *input)
{
	int	num_chunks;
	char	**arr;

	num_chunks = count_chunks(input);
	arr = (char **)ft_calloc(sizeof(char *) * (num_chunks + 1));
	if (!arr)
		return (0);
	init_arr(arr, input);
	arr[num_chunks] = 0;
	return (arr);
}
