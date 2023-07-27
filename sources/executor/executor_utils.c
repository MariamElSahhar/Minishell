/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:01:46 by szerisen          #+#    #+#             */
/*   Updated: 2023/07/27 13:17:04 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
It takes two arguments: split_str, which is an array of strings,
 and new_str, which is a string.
It initializes a variable tmp with a duplicate of the first
string in split_str (split_str[0]).
It then enters a loop starting from index 1 and
iterates through the split_str array.
In each iteration, it assigns tmp to new_str, and then
joins new_str with a space character using ft_strjoin to
create add_space.
It frees the memory allocated for new_str, assigns tmp
to add_space using ft_strjoin to concatenate add_space
with the current string in split_str[i], and frees the
memory allocated for add_space.
The loop continues until all elements of split_str have
been processed.
Finally, it assigns tmp to new_str and returns new_str.
*/
char	*join_split_str(char **split_str, char *new_str)
{
	char	*tmp;
	char	*add_space;
	int		i;

	tmp = ft_strdup(split_str[0]);
	i = 1;
	while (split_str[i])
	{
		new_str = tmp;
		add_space = ft_strjoin(new_str, " ");
		free(new_str);
		tmp = ft_strjoin(add_space, split_str[i]);
		free(add_space);
		i++;
	}
	new_str = tmp;
	return (new_str);
}

int	check_redir_helper(int type, t_redir *dir)
{
	int	fd;

	if (type == OPEN)
	{
		if (handle_open(dir))
			return (EXIT_FAILURE);
	}
	else if (type == WRITE || type == APPEND)
	{
		if (handle_outfile(dir))
			return (EXIT_FAILURE);
	}
	else if (type == IGNORE)
	{
		fd = open(dir->path, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: infile: No such file or directory\n",
				STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		close (fd);
	}
	return (EXIT_SUCCESS);
}

void	parent_export(t_utils *utils, t_cmds *cmds)
{
	char	**tmp;
	int		i;

	i = 1;
	if (!cmds->args[1] || cmds->args[1][0] == '\0')
		return ;
	else
	{
		while (cmds->args[i])
		{
			if (!check_parameter(cmds->args[i])
				&& !variable_exist(utils, cmds->args[i])
				&& !invalid_identifier(cmds->args[i], 1))
			{
				tmp = add_var(utils->envp, cmds->args[i]);
				free_double_ptr((void **)utils->envp);
				utils->envp = tmp;
			}
			else if ((invalid_identifier(cmds->args[i], 1)
					|| check_parameter(cmds->args[i])))
				return ;
			i++;
		}
	}
	return ;
}
