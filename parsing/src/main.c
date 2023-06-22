/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:09:53 by melsahha          #+#    #+#             */
/*   Updated: 2023/06/22 14:38:51 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

// init the utils struct with default info
int	init_utils(t_utils *utils, char *input)
{
	utils->input = input;
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

// checks input and parses to a util struct
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
	// write(STDOUT_FILENO, CLEAR_SCREEN_SEQ, ft_strlen(CLEAR_SCREEN_SEQ));
	return (utils);
}

// print utils for visualization
void	print_utils(t_utils *utils)
{
	t_cmds	*c_ptr;
	int		i;
	t_redir	*r_ptr;

	c_ptr = utils->cmds;
	while (c_ptr)
	{
		printf("cmd: %s\n", c_ptr->command);
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

// reads line and updates history
void	main_loop(void)
{
	t_utils	*utils;

	while (1)
	{
		utils = (t_utils *)ft_calloc(1, sizeof(t_utils));
		utils->input = ft_strdup("hello");
		if (!utils->input)
			return ;
		add_history((const char *) utils->input);
		utils = parse_input(utils->input);
		if (!utils)
			printf("parse error\n");
		else
			print_utils(utils);
		free(utils->input);
		// free_utils(utils);
	}
}

void	signal_handler(int sig)
{
	if ((sig == SIGQUIT && !rl_line_buffer[0])
		|| (sig == SIGINT && rl_line_buffer[0]))
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line(">", 0);
		rl_redisplay();
	}
	else
		exit(0);
}

int	main(void)
{
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler);
	main_loop();
	return (0);
}
