/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:15:15 by szerisen          #+#    #+#             */
/*   Updated: 2023/07/14 14:46:56 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// initializes utils values
int	implement_utils(t_utils *utils)
{
	utils->cmds = NULL;
	utils->reset = false;
	utils->pid = NULL;
	utils->heredoc = false;
	g_global.stop_heredoc = 0;
	g_global.in_cmd = 0;
	g_global.in_heredoc = 0;
	return (1);
}

// frees memory associated with a cmd
void	free_cmd(t_cmds *cmd)
{
	t_redir	*ptr;
	t_redir	*del;

	if (cmd->hd_file_name)
		free(cmd->hd_file_name);
	if (cmd->args)
		free_double_ptr((void **) cmd->args);
	ptr = cmd->redirections;
	while (ptr)
	{
		del = ptr;
		ptr = ptr->next;
		if (del->path)
			free(del->path);
		free(del);
	}
	if (cmd)
		free(cmd);
}

// resets utils variables
int	reset_utils(t_utils *utils)
{
	t_cmds	*ptr;
	t_cmds	*del;

	ptr = utils->cmds;
	while (ptr)
	{
		del = ptr;
		ptr = ptr->next;
		free_cmd(del);
	}
	if (utils->input)
		free(utils->input);
	if (utils->pid)
		free(utils->pid);
	utils->reset = true;
	return (1);
}

// free memory on exit
void	free_utils(t_utils *utils)
{
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	close(STDIN_FILENO);
	if (utils->pwd)
		free(utils->pwd);
	if (utils->old_pwd)
		free(utils->old_pwd);
	free_double_ptr((void **)utils->envp);
	free_double_ptr((void **)utils->paths);
}

// duplicates the passed string
char	**ft_arrdup(char **arr)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(i + 1, sizeof(char *));
	if (!rtn)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		rtn[i] = ft_strdup(arr[i]);
		if (rtn[i] == NULL)
		{
			free_double_ptr((void **) rtn);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}
