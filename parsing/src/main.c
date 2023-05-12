/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:09:53 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/11 18:09:23 by melsahha         ###   ########.fr       */
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

//TO-DO: take pipes in quotation marks into account
t_list	*parse_input(char *input)
{
	// char	**split;

	// split = split_input(input);

	// int	i = -1;
	// while (split && split[++i])
	// 	printf("%s\n", split[i]);
	check_input(input);
	return (0);
	// t_list	*list;

	// list = (t_list *)ft_calloc(1, sizeof(t_list));
	// list->pipes = count_pipes(input);
	// list->command_list = (t_command *)ft_calloc(list->pipes + 1, sizeof(t_command));
	// list->command_list = get_commands(split);
	// free_double_ptr(split);
}

void	main_loop(int sig)
{
	char	*input;
	t_list	*list;

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
		list = parse_input(input);
		// if (!list)
		// 	return (0);
		free(list);
		free(input);
	}
}

int	main(void)
{
	// signal(SIGINT, &main_loop);

	main_loop(0);
	return (0);
}
