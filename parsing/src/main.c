/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:09:53 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/10 20:21:07 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	count_pipes(char *input)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = 0;
	while (input[i])
	{
		if (input[i] == '|')
			pipes ++;
		i++;
	}
	return (pipes);
}

t_command	*get_commands(char **split)
{
	
}

//TO-DO: take pipes in quotation marks into account
t_list	*parse_input(char *input)
{
	t_list	*list;
	char	**split;

	list = (t_list *)ft_calloc(1, sizeof(t_list));
	list->pipes = count_pipes(input);
	list->command_list = (t_command *)ft_calloc(list->pipes + 1, sizeof(t_command));
	split = split_input(input);
	list->command_list = get_commands(split);
	free_double_ptr(split);
}

int	main(void)
{
	char	*input;
	t_list	*list;

	while (1)
	{
		input = readline("> ");
		add_history((const char *) input);
		list = parse_input(input);
		free(list);
		free(input);
	}
	return (0);
}
