/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:29:44 by melsahha          #+#    #+#             */
/*   Updated: 2023/07/05 17:36:24 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ints the argument list
char	**init_args(t_word *start)
{
	t_word	*ptr;
	int		count;
	char	**args;

	ptr = start;
	count = 0;
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type == ARG)
			count ++;
		ptr = ptr->next;
	}
	ptr = start;
	args = (char **)ft_calloc(count + 2, sizeof(char *));
	if (!args)
		ft_error(1, 0);
	count = 1;
	while (args && ptr && ptr->type != PIPE)
	{
		if (ptr->type == ARG)
			args[count++] = ptr->cont;
		ptr = ptr->next;
	}
	return (args);
}

// pushed command to list
void	push_cmd(t_utils *utils, t_cmds *cmd)
{
	t_cmds	*ptr;

	cmd->builtin = builtin_arr(cmd->command);
	last_in_redir(cmd);
	last_out_redir(cmd);
	ptr = utils->cmds;
	if (!ptr)
		utils->cmds = cmd;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = cmd;
		cmd->prev = ptr;
	}
}

// changes i to the index of the end of the flag
void	end_of_flag(char *input, int *i)
{
	while (input[(*i)] && !is_space(input[(*i)]) && !is_symbol(input[(*i)]))
	{
		while (input[(*i)] && !(is_space(input[(*i)])
				|| is_symbol(input[(*i)]) || is_quote(input[(*i)])))
			(*i)++;
		while (input[(*i)] && is_quote(input[(*i)]))
			skip_quotes(i, input);
	}
}


// returns value of the variable var in utils.envp
char	*ft_getenv(char *var, t_utils *utils)
{
	int		i;
	char	**value;
	char	c;

	i = -1;
	c = '=';
	while (utils->envp[++i])
	{
		value = ft_split(utils->envp[i], '=');
		if (!value)
		{
			ft_error(1, 0);
			return (0);
		}
		if (!ft_strncmp(var, value[0], ft_strlen(value[0]))
			&& !ft_strncmp(var, value[0], ft_strlen(var)))
		{
			free(value[0]);
			return (value[1]);
		}
		free_double_ptr((void **) value);
	}
	return ("");
}
