/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:09:53 by melsahha          #+#    #+#             */
/*   Updated: 2023/06/23 16:59:12 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_pipes(t_utils *utils)
{
	t_cmds	*ptr;
	int		count;

	count = 0;
	ptr = utils->cmds;
	while (ptr)
	{
		ptr = ptr->next;
		count++;
	}
	return (count - 1);
}

// checks input and parses to a util struct
int	parse_input(t_utils *utils)
{
	t_split	*split;
	int		sorted;

	if (!check_input(utils->input))
		return (0);
	split = split_input(utils->input);
	if (!split)
		return (0);
	sorted = sort_tokens(split, utils);
	free_split(split);
	utils->pipes = count_pipes(utils);
	// write(STDOUT_FILENO, CLEAR_SCREEN_SEQ, ft_strlen(CLEAR_SCREEN_SEQ));
	return (sorted);
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

/* // reads line and updates history
void	main_loop(void)
{
	t_utils	*utils;

	// while (1)
	// {
		utils = (t_utils *)ft_calloc(1, sizeof(t_utils));
		utils->input = ft_strdup(">>>");
		if (!utils->input)
			return ;
		add_history((const char *) utils->input);
		if (!parse_input(utils))
			printf("parse error\n");
		else
			print_utils(utils);
		free_utils(utils);
	// }
}
 */
/*
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
 */

/* int	main(void)
{
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler);
	main_loop();
	return (0);
}
 */
