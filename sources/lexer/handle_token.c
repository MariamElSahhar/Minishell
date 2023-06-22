/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:44:58 by szerisen          #+#    #+#             */
/*   Updated: 2023/05/31 20:09:12 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "lexer.h"
/*
Parameters: c (int)
Returns: The corresponding token value (enum t_tokens) based on the input character c.
This function checks the input character c against a static array token_arr that holds pairs of characters and their corresponding token values.
If c matches any character in the array, the corresponding token value is returned.
If there is no match, it returns 0, indicating an invalid token.
*/
t_tokens	check_token(int c)
{
	static int	token_arr[3][2] = {
	{'|', PIPE},
	{'>', GREAT},
	{'<', LESS},
	};
	int			i;

	i = 0;
	while (i < 3)
	{
		if (token_arr[i][0] == c)
			return (token_arr[i][1]);
		i++;
	}
	return (0);
}
/*
Parameters: str (char array), i (int), lexer_list (pointer to a pointer of t_lexer)
Returns: The number of characters consumed by the token handling (either 0, 1, or 2).
This function is responsible for handling tokens in the input string str at the specified 
index i and updating the lexer_list accordingly.
It first calls check_token to determine the token type based on the character at str[i].
If the token is a double-greater-than (>>) or a double-less-than (<<), it checks the next character 
using check_token as well. If it matches the corresponding token, it adds the appropriate node to the 
lexer_list using add_node (presumably defined elsewhere).
If the token is a single character token (e.g., |, >, <), it adds the corresponding node to the lexer_list.
Finally, it returns the number of characters consumed by the token handling (0, 1, or 2) to allow for the 
next iteration to resume parsing from the appropriate position.
*/
int	handle_token(char *str, int i, t_lexer **lexer_list)
{
	t_tokens	token;

	token = check_token(str[i]);
	if (token == GREAT && check_token(str[i + 1]) == GREAT)
	{
		if (!add_node(NULL, GREAT_GREAT, lexer_list))
			return (-1);
		return (2);
	}
	else if (token == LESS && check_token(str[i + 1]) == LESS)
	{
		if (!add_node(NULL, LESS_LESS, lexer_list))
			return (-1);
		return (2);
	}
	else if (token)
	{
		if (!add_node(NULL, token, lexer_list))
			return (-1);
		return (1);
	}	
	return (0);
}
