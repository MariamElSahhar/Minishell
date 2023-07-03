/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:29:44 by melsahha          #+#    #+#             */
/*   Updated: 2023/07/03 20:04:58 by melsahha         ###   ########.fr       */
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
		if (ptr->type == FLAG || ptr->type == ARG)
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
		if (ptr->type == FLAG || ptr->type == ARG)
			args[count++] = ptr->cont;
		ptr = ptr->next;
	}
	return (args);
}

// checks if command is a builtin and assigns it the builtin function
void	check_builtin(t_cmds *cmd)
{
	if (!ft_strncmp(cmd->command, "cd", ft_strlen(cmd->command)))
		cmd->builtin = &m_cd;
	else if (!ft_strncmp(cmd->command, "echo", ft_strlen(cmd->command)))
		cmd->builtin = &m_echo;
	else if (!ft_strncmp(cmd->command, "env", ft_strlen(cmd->command)))
		cmd->builtin = &m_env;
	else if (!ft_strncmp(cmd->command, "exit", ft_strlen(cmd->command)))
		cmd->builtin = &m_exit;
	else if (!ft_strncmp(cmd->command, "export", ft_strlen(cmd->command)))
		cmd->builtin = &m_export;
	else if (!ft_strncmp(cmd->command, "pwd", ft_strlen(cmd->command)))
		cmd->builtin = &m_pwd;
	else if (!ft_strncmp(cmd->command, "unset", ft_strlen(cmd->command)))
		cmd->builtin = &m_unset;
}

// pushed command to list
void	push_cmd(t_utils *utils, t_cmds *cmd)
{
	t_cmds	*ptr;

	check_builtin(cmd);
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
