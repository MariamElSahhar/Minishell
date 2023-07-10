/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:15:15 by szerisen          #+#    #+#             */
/*   Updated: 2023/07/10 18:26:49 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
This function initializes the utils
 structure with default values and
 sets up the environment.
It sets various variables and flags
 in the utils structure to their initial values.
It calls the parse_envp function to
 parse the environment variables and
 store them in the utils structure.
It calls the init_signals function to
 set up signal handling for the minishell.
*/
int	implement_utils(t_utils *utils)
{
	utils->cmds = NULL;
	utils->reset = false;
	utils->pid = NULL;
	utils->heredoc = false;
	g_global.stop_heredoc = 0;
	g_global.in_cmd = 0;
	g_global.in_heredoc = 0;
	parse_envp(utils);
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
	if (utils->pwd)
		free(utils->pwd);
	if (utils->old_pwd)
		free(utils->old_pwd);
	free_double_ptr((void **)utils->envp);
	free_double_ptr((void **)utils->paths);
	utils->reset = true;
	return (1);
}

/*
ft_arrdup function:

Parameter: arr (array of char pointers)
Returns: A duplicated array of strings.
This function creates a duplicate of an array
of strings.
It first calculates the number of strings in
the array by iterating until it encounters a
NULL pointer.
Then it allocates memory for a new array rtn
of size i + 1, where i is the number of strings
 in the original array.
Next, it iterates through each string in the
original array, duplicates it using ft_strdup,
 and stores
the duplicated string in the new array rtn.
If any allocation fails during the process,
it frees the partially allocated memory and returns NULL.
If the duplication is successful for all
strings, it returns the duplicated array rtn.
*/
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
