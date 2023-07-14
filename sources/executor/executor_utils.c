/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:01:46 by szerisen          #+#    #+#             */
/*   Updated: 2023/07/14 15:43:00 by szerisen         ###   ########.fr       */
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
	return (EXIT_SUCCESS);
}
