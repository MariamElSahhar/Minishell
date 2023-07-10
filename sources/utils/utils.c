/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:15:15 by szerisen          #+#    #+#             */
/*   Updated: 2023/07/10 18:12:26 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			free_arr(rtn);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}
