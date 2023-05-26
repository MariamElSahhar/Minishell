/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:09:53 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/26 19:29:11 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

/* int	count_pipes(char *input)
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
*/
t_utils	*parse_input(char *input)
{
	t_split	*split;
	// t_utils	*utils;

	if (!check_input(input))
		return (0);
	split = split_input(input);
	if (!split)
		return (0);
	//3+ redirections in a row, pipe after redirection
	//empty quotes are invalid unless in path name (after redirection)
	if(!check_split(split))
	{
		printf("error\n");
		free_split(split);
		return (0);
	}

	// utils = tokenize_input(split);
	// return (split);
	return (0);
}

void	main_loop(int sig)
{
	char	*input;
	t_utils	*utils;

	sig = 0;
	while (1)
	{
		input = readline("> ");
		if (!input || !ft_strlen(input))
		{
			printf("exit");
			return ;
		}
		add_history((const char *) input);
		utils = parse_input(input);
		// if (!utils)
		// 	return (0);
		// free_utils(utils);
		free(input);
	}
}

int	main(void)
{
	// signal(SIGINT, &main_loop);

	main_loop(0);
	return (0);
}
