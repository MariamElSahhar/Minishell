/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:01:46 by szerisen          #+#    #+#             */
/*   Updated: 2023/06/23 18:26:06 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
It takes two arguments: split_str, which is an array of strings, and new_str, which is a string.
It initializes a variable tmp with a duplicate of the first string in split_str (split_str[0]).
It then enters a loop starting from index 1 and iterates through the split_str array.
In each iteration, it assigns tmp to new_str, and then joins new_str with a space character using ft_strjoin to create add_space.
It frees the memory allocated for new_str, assigns tmp to add_space using ft_strjoin to concatenate add_space with the current string in split_str[i], and frees the memory allocated for add_space.
The loop continues until all elements of split_str have been processed.
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
/*
It takes a single argument double_arr, which is an array of strings.
It first calls join_split_str with double_arr and NULL as arguments to join the strings in double_arr into a single string, which is assigned to joined_str.
It then frees the memory allocated for double_arr using free_arr.
Next, it calls ft_split to split joined_str into an array of strings, using the space character (' ') as the delimiter. The resulting array is assigned to ret.
It frees the memory allocated for joined_str.
After that, it calls join_split_str again, this time with ret and NULL as arguments, to join the strings in ret into a single string, which is assigned to joined_str.
It frees the memory allocated for ret using free_arr.
Finally, it calls ft_split once again to split joined_str into an array of strings, using the space character (' ') as the delimiter, and returns the resulting array.
*/
/* char	**resplit_str(char **double_arr)
{
	char	**ret;
	char	*joined_str;

	joined_str = join_split_str(double_arr, NULL);
	free_arr(double_arr);
	ret = ft_split(joined_str, ' ');
	free(joined_str);
	joined_str = join_split_str(ret, NULL);
	free_arr(ret);
	ret = ft_split(joined_str, ' ');
	free(joined_str);
	return (ret);
}
 */
