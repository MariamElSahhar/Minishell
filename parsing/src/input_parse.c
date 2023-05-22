/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:39:14 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/17 17:44:55 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	skip_quotes(int *i, char *input)
{
	int	quote;

	quote = input[*i];
	(*i) = (*i) + 1;
	while (input[*i] && input[*i] != quote)
		(*i) = (*i) + 1;
	if (input[*i] && input[*i] == quote)
		(*i) = (*i) + 1;
}

static int	count_pipes(char *input)
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
			skip_quotes(&i, input);
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

//FIX THIS
static void	push_cmd(t_cmds *list, t_cmds *new_cmd)
{
	t_cmds	*ptr;

	if (!list || !new_cmd)
		return ;
	ptr = list;
	if (!ptr)
	{
		list = new_cmd;
		list->next = 0;
		list->prev = 0;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new_cmd;
	new_cmd->prev = ptr;
	new_cmd->next = 0;
}

/* static void	cmd_args(t_cmds *cmd)
{
	int	i;

	i = 0;

} */

static t_cmds	*init_cmd(char *input, int *i)
{
	int		j;
	char	*cmd_str;
	t_cmds	*cmd;

	cmd = (t_cmds *)ft_calloc(1, sizeof(t_cmds));
	j = *i;
	if (input[(*i)] == '|')
		(*i)++;
	while (input[(*i)] && input[(*i)] != '|')
	{
		while (input[(*i)] && is_quote(input[(*i)]))
			in_quotes(&(*i), input);
		(*i)++;
	}
	cmd_str = (char *)ft_calloc((*i) - j + 1, sizeof(char));
	while (j < (*i))
	{
		cmd_str[j] = input[j];
		j++;
	}
	return (0);
	// cmd_redirect(cmd);
	// cmd_args(cmd);
}

static t_cmds	*parse_cmds(char *input, int num)
{
	t_cmds	*commands;
	t_cmds	*curr;
	int		i;
	int		cmd_num;

	commands = (t_cmds *)ft_calloc(num, sizeof(t_cmds));
	if (!commands)
		return (0);
	i = 0;
	cmd_num = 0;
	while (cmd_num < num)
	{
		curr = init_cmd(input, &i);
		push_cmd(commands, curr);
		cmd_num++;
	}
	// printf("%s\n", (input, '|'));
	return (0);
}


t_utils	*split_input(char *input)
{
	t_utils	*utils;

	utils = (t_utils *)ft_calloc(1, sizeof(t_utils));
	if (!utils)
		return (0);
	utils->args = input;
	utils->pipes = count_pipes(input);
	utils->cmds = parse_cmds(input, utils->pipes);
	// list->command_list = get_commands(input, list->pipes);
	// if (!list->command_list)
	// 	return (0);
	return (utils);
}
