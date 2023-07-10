/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:44:48 by szerisen          #+#    #+#             */
/*   Updated: 2023/07/10 18:39:40 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	minishell_loop(t_utils *utils)
{
	while (1)
	{
		utils->input = readline(READLINE_MSG);
		implement_utils(utils);
		if (!utils->input)
		{
			reset_utils(utils);
			rl_replace_line("exit", 0);
			exit(EXIT_SUCCESS);
		}
		else if (utils->input[0] == '\0')
		{
			reset_utils(utils);
			continue ;
		}
		add_history(utils->input);
		if (parse_input(utils))
			prepare_executor(utils);
		reset_utils(utils);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_utils	utils;

	if (argc != 1 || argv[1])
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
	init_signals();
	printf("\n%s\n\n", WELCOME_MSG);
	utils.envp = ft_arrdup(envp);
	parse_envp(&utils);
	find_pwd(&utils);
	minishell_loop(&utils);
	free_utils(&utils);
	return (0);
}
