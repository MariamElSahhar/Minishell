/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:09:53 by melsahha          #+#    #+#             */
/*   Updated: 2023/06/27 15:13:34 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// sorts tokens to list of commands
int	sort_tokens(t_split *split, t_utils *utils)
{
	t_word	*ptr;
	t_cmds	*new_cmd;

	ptr = split->first;
	while (ptr)
	{
		new_cmd = (t_cmds *)ft_calloc(1, sizeof(t_cmds));
		if (!new_cmd)
			return(!ft_error(1, 0));
		new_cmd->args = init_args(ptr);
		if (!new_cmd->args)
			return (0);
		while (ptr && ptr->type != PIPE && new_cmd)
		{
			if (ptr->type == CMD)
				new_cmd->command = ptr->cont;
			else if (ptr->type == REDIR)
				new_cmd = push_redir(new_cmd, ptr);
			ptr = ptr->next;
		}
		if (!new_cmd)
			return (0);
		new_cmd->args[0] = new_cmd->command;
		push_cmd(utils, new_cmd);
		if (ptr && ptr->type == PIPE)
			ptr = ptr->next;
	}
	return (1);
}

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
	split = split_input(utils->input, utils);
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

