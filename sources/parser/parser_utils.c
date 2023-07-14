/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:29:44 by melsahha          #+#    #+#             */
/*   Updated: 2023/07/14 20:53:05 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// initializes a cmd struct
t_word	*init_cmd(t_word *ptr, t_cmds *new_cmd)
{
	new_cmd->args = init_args(ptr);
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type == CMD)
			new_cmd->command = ptr->cont;
		else if (ptr->type == REDIR)
			new_cmd = push_redir(new_cmd, ptr);
		ptr = ptr->next;
	}
	new_cmd->args[0] = new_cmd->command;
	return (ptr);
}

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

// returns value of the variable var in utils.envp
char	*ft_getenv(char *var, t_utils *utils)
{
	int		i;
	char	**value;
	char	*ret;

	i = -1;
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
			if (value[1])
				ret = ft_strdup(value[1]);
			else
				ret = ft_calloc(1, sizeof(char));
			free_double_ptr((void **) value);
			return (ret);
		}
		free_double_ptr((void **) value);
	}
	return ("");
}

// replace $? with the error code
char	*expand_err(char *cont, int *i)
{
	char	*err;

	err = ft_itoa(g_global.error_code);
	(*i) = (*i) + 2;
	cont = replace_env(cont, i, err, 1);
	if (!cont)
		return (0);
	(*i) = 0;
	return (cont);
}
