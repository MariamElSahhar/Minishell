/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:09:53 by melsahha          #+#    #+#             */
/*   Updated: 2023/06/02 17:49:05 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	init_utils(t_utils *utils, char *input)
{
	utils->input = input;
	utils->envp = environ;
	utils->pwd = (char *)ft_calloc(4069, sizeof(char));
	utils->old_pwd = (char *)ft_calloc(4069, sizeof(char));
	if (!getcwd(utils->pwd, 4096) || !getcwd(utils->pwd, 4096))
		return (0);
	utils->pid = (int *)ft_calloc(2, sizeof(int));
	if (!utils->pid)
		return (0);
	utils->pid[0] = getpid();
	return (1);
}

t_utils	*parse_input(char *input)
{
	t_split	*split;
	t_utils	*utils;

	if (!check_input(input))
		return (0);
	split = split_input(input);
	if (!split)
		return (0);
	utils = sort_tokens(split);
	if (!utils || !init_utils(utils, input))
		return (0);
	// print_split(split);
	return (utils);
}

void	print_utils(t_utils *utils)
{
	t_cmds	*c_ptr;
	int		i;
	t_redir	*r_ptr;

	c_ptr = utils->cmds;
	while (c_ptr)
	{
		printf("%s\n", c_ptr->command);
		i = 0;
		while (c_ptr->args[i])
			printf("arg: %s\n", c_ptr->args[i++]);
		r_ptr = c_ptr->redirections;
		while (r_ptr)
		{
			printf("%i - %s\n", r_ptr->type, r_ptr->path);
			r_ptr = r_ptr->next;
		}
		c_ptr = c_ptr->next;
	}
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
		if (!utils)
			printf("parse error\n");
		print_utils(utils);
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
