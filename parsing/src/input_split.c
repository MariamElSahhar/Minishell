/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:58:39 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/22 18:30:21 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	is_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	allocate_cmd_args(t_cmds *cmd, char *input, int i)
{
	int	cmd_cnt;
	int	arg_cnt;

	cmd_cnt = 0;
	arg_cnt = 0;
	while (input[i])
	{
		while (input[i] && is_space(input[i]))
			i++;
		if ()
	}
}

t_cmds	*add_item(t_utils *utils, int *i, char *input)
{
	t_cmds	*new_cmd;
	int		j;

	j = *i;
	new_cmd = (t_cmds *)ft_calloc(1, sizeof(t_cmds));
	allocate_cmd_args(new_cmd, input, j);
	while (input[j])
	{
		j++;
	}
	return (new_cmd);
}

void	itemize(char *input, t_utils *utils)
{
	int		i;
	t_cmds	*new_cmd;
	t_cmds	*last_cmd;

	i = 0;
	last_cmd = utils->cmds;
	while (input && input[i])
	{
		while(input[i] && is_space(input[i]))
			i++;
		if (input[i] && !is_space(input[i]))
		{
			new_cmd = add_item(utils, &i, input);
			if (!utils->cmds)
				utils->cmds = new_cmd;
			new_cmd->next = 0;
			new_cmd->prev = last_cmd;
			last_cmd = new_cmd;
		}
	}
}

t_utils	*split_input(char *input)
{
	t_utils	*utils;

	utils = (t_utils *)ft_calloc(1, sizeof(t_utils));
	utils->args = input;
	itimize(input, utils);
	return (utils);
}
