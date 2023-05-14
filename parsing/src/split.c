/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:39:14 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/14 16:27:43 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	in_quotes(int *i, char *input)
{
	int	quote;

	quote = input[*i];
	(*i) = (*i) + 1;
	while (input[*i] && input[*i] != quote)
		(*i) = (*i) + 1;
	if (input[*i] && input[*i] == quote)
		(*i) = (*i) + 1;
}

static int	count_commands(char *input)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	while (input && input[i])
	{
		while (input[i] && !is_quote(input[i]) && input[i] != '|')
			i++;
		while (input[i] && is_quote(input[i]))
			in_quotes(&i, input);
		while (input[i] && !is_quote(input[i]) && input[i] != '|')
			i++;
		if (input[i] && input[i] == '|' && !is_quote(input[i]))
		{
			count++;
			i++;
		}
	}
	printf("%i commands\n", count);
	return (count);
}

/* static t_command	*get_commands(char *input, int num)
{
	t_command	*commands;

	commands = (t_command *)ft_calloc(num, sizeof(t_command));
	if (!commands)
		return (0);
	// printf("%s\n", (input, '|'));
	return (0);
}
 */
t_input	*split_input(char *input)
{
	t_input	*list;

	list = (t_input *)ft_calloc(1, sizeof(t_input));
	if (!list)
		return (0);
	list->pipes = count_commands(input);
	// list->command_list = get_commands(input, list->pipes);
	// if (!list->command_list)
	// 	return (0);
	return (list);
}
