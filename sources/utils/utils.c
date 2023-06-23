/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:15:15 by szerisen          #+#    #+#             */
/*   Updated: 2023/06/23 18:37:38 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
find_matching_quote function:

Parameters: line (char array), i (int), num_del (pointer to int), del (int)
Returns: The number of characters between the current position i and the matching closing quote.
This function is used to find the matching closing quote (either single quote ' or double quote ")
in a given line of text.
It starts from the position i and iterates through the characters until it finds the closing quote del.
While iterating, it also counts the number of delimiter characters encountered (num_del).
If the closing quote is found, it increments num_del by 1 and returns the number of characters between
the opening and closing quotes.
This function is likely used in the count_quotes function to handle quoted strings properly.
*/
int	find_matching_quote(char *line, int i, int *num_del, int del)
{
	int	j;

	j = i + 1;
	*num_del += 1;
	while (line[j] && line[j] != del)
		j++;
	if (line[j] == del)
		*num_del += 1;
	return (j - i);
}
/*
count_quotes function:
----------------------
Parameter: line (char array)
Returns: 1 if the number of single quotes ' and double quotes " is even and balanced, 0 otherwise.
This function counts the number of single quotes and double quotes in the given line.
It iterates through the characters of the line and whenever it encounters a single quote or
double quote, it uses the find_matching_quote function to find the matching closing quote.
If the count of either single quotes or double quotes is odd, indicating an imbalance, the function returns 0.
If both counts are even, it returns 1 to indicate that the quotes are balanced.
*/
int	count_quotes(char *line)
{
	int	i;
	int	s;
	int	d;

	s = 0;
	d = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == 34)
			i += find_matching_quote(line, i, &d, 34);
		if (line[i] == 39)
			i += find_matching_quote(line, i, &s, 39);
	}
	if ((d > 0 && d % 2 != 0) || (s > 0 && s % 2 != 0))
		return (0);
	return (1);
}
/*
ft_arrdup function:

Parameter: arr (array of char pointers)
Returns: A duplicated array of strings.
This function creates a duplicate of an array of strings.
It first calculates the number of strings in the array by iterating until it encounters a NULL pointer.
Then it allocates memory for a new array rtn of size i + 1, where i is the number of strings in the original array.
Next, it iterates through each string in the original array, duplicates it using ft_strdup, and stores
the duplicated string in the new array rtn.
If any allocation fails during the process, it frees the partially allocated memory and returns NULL.
If the duplication is successful for all strings, it returns the duplicated array rtn.
*/
char	**ft_arrdup(char **arr)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1);
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

void	free_double_ptr(void **ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	if (ptr)
		free(ptr);
}
