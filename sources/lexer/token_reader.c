/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:44:50 by szerisen          #+#    #+#             */
/*   Updated: 2023/06/01 21:19:46 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

int	skip_spaces(char *str, int i)
{
	int	j;

	j = 0;
	while (is_whitespace(str[i + j]))
		j++;
	return (j);
}
/*
This function creates a new node in the t_lexer linked list and adds it to the end.
It takes three arguments: a string str representing the content of the node, a token value representing the 
token type, and a pointer to the lexer_list representing the head of the linked list.
It calls the ft_lexernew function to create a new t_lexer node with the provided content and token type.
If the node creation is successful, it calls the ft_lexeradd_back function to add the new node to the end of
the linked list. It returns 1 to indicate success or 0 if the node creation fails.
*/
int	add_node(char *str, t_tokens token, t_lexer **lexer_list)
{
	t_lexer	*node;

	node = ft_lexernew(str, token);
	if (!node)
		return (0);
	ft_lexeradd_back(lexer_list, node);
	return (1);
}
/*
This function reads a sequence of characters from the input string str starting from position i until it encounters 
a whitespace character or a token character.
It takes three arguments: the starting position i, the input string str, and a pointer to the lexer_list.
It iterates through the string from str[i] onward until it finds a whitespace character or a token character 
(checked using the check_token function).
It handles quotes by calling the handle_quotes function to skip over quoted sections within the word.
If the iteration ends without encountering a whitespace or token character, it creates a new node using the 
add_node function with the extracted word as the content and a token value of 0 (indicating it is a word).
If the node creation fails, it returns -1 to indicate an error.
Otherwise, it returns the number of characters read.
*/
int	read_words(int i, char *str, t_lexer **lexer_list)
{
	int	j;

	j = 0;
	while (str[i + j] && !(check_token(str[i + j])))
	{
		j += handle_quotes(i + j, str, 34);
		j += handle_quotes(i + j, str, 39);
		if (is_whitespace(str[i + j]))
			break ;
		else
			j++;
	}
	if (!add_node(ft_substr(str, i, j), 0, lexer_list))
		return (-1);
	return (j);
}
/*
This is the main function that tokenizes the input string and builds the t_lexer linked list.
It takes a pointer to a t_utils struct called utils, which contains information about the input string and 
the lexer list. It initializes the variable i to 0. It enters a loop that iterates through each argument in the utils->args array.
It skips leading spaces in the input string by calling the skip_spaces function and increments i accordingly.
If the character at utils->args[i] is a token character (checked using check_token), it calls the handle_token 
function to handle the token and update the lexer list.
Otherwise, it calls the read_words function to read a sequence of characters and add a word node to the lexer list.
If an error occurs during tokenization (e.g., memory allocation failure)
*/
int	token_reader(t_utils *utils)
{
	int		i;
	int		j;

	i = 0;
	while (utils->args[i])
	{
		j = 0;
		i += skip_spaces(utils->args, i);
		if (check_token(utils->args[i]))
			j = handle_token(utils->args, i, &utils->lexer_list);
		else
			j = read_words(i, utils->args, &utils->lexer_list);
		if (j < 0)
			return (0);
		i += j;
	}
	return (1);
}
