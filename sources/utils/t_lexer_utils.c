/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lexer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:35:35 by szerisen          #+#    #+#             */
/*   Updated: 2023/05/29 22:00:10 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
/*
This function creates a new node for the t_lexer linked list.
It takes two arguments: str, which represents the string associated with the node, and token, which represents the token type.
It allocates memory for a new t_lexer structure using malloc.
If the allocation fails, it returns NULL.
Otherwise, it initializes the str and token members of the new node with the provided values.
The i member is set based on a static variable i, which is incremented each time a new node is created.
The next and prev pointers are initialized to NULL.
Finally, the function returns the newly created node.

*/
t_lexer	*ft_lexernew(char *str, int token)
{
	t_lexer		*new_element;
	static int	i = 0;

	new_element = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_element)
		return (0);
	new_element->str = str;
	new_element->token = token;
	new_element->i = i++;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}
/*
This function adds a new node to the end of the t_lexer linked list.
It takes two arguments: the address of the list pointer (**lst) and the new node to be added (*new).
It uses a temporary variable tmp to traverse the list and find the last node.
If the list pointer is NULL, meaning the list is empty, the new node becomes the first node.
Otherwise, it iterates through the list until it reaches the last node (where tmp->next is NULL).
It assigns the next pointer of the last node to the new node and updates the prev pointer of the new node to point to the last node.
By doing so, the new node becomes the last node in the list.
If the list was empty, the new node is now the first and last node.
Finally, the function returns, and the list is updated accordingly.
*/
void	ft_lexeradd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}
