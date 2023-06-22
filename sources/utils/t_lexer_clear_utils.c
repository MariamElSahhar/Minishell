/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lexer_clear_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:35:13 by szerisen          #+#    #+#             */
/*   Updated: 2023/05/29 19:59:50 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
/*
This function clears a single node in the t_lexer linked list.
It frees the memory allocated for the str member of the node and sets it to NULL.
Then, it frees the memory allocated for the node itself and sets it to NULL.
Finally, it returns NULL to indicate that the node has been cleared.
*/
t_lexer	*ft_lexerclear_one(t_lexer **lst)
{
	if ((*lst)->str)
	{
		free((*lst)->str);
		(*lst)->str = NULL;
	}
	free(*lst);
	*lst = NULL;
	return (NULL);
}
/*
This function deletes the first node in the t_lexer linked list.
It takes the address of the list pointer as an argument (**lst).
It stores the first node in the node variable and updates the list pointer to point to the next node.
The ft_lexerclear_one function is called to clear the memory for the node.
If the list pointer is not NULL after updating, it updates the prev pointer of the new first node to NULL.
*/
void	ft_lexerdel_first(t_lexer **lst)
{
	t_lexer	*node;

	node = *lst;
	*lst = node->next;
	ft_lexerclear_one(&node);
	if (*lst)
		(*lst)->prev = NULL;
}
/*
This function deletes a node with a specific key value from the t_lexer linked list.
It takes the address of the list pointer (**lst) and the key value as arguments.
It traverses the linked list to find the node with the matching key value.
If the first node has the matching key, it calls ft_lexerdel_first to delete it.
Otherwise, it iterates through the list until it finds the node with the matching key.
It updates the next pointer of the previous node to skip the node to be deleted.
If the node to be deleted is not the last node, it updates the prev pointer of the next node to point to the previous node.
The memory for the node is cleared using ft_lexerclear_one.
Finally, the function updates the list pointer to the original starting node.
*/
void	ft_lexerdelone(t_lexer **lst, int key)
{
	t_lexer	*node;
	t_lexer	*prev;
	t_lexer	*start;

	start = *lst;
	node = start;
	if ((*lst)->i == key)
	{
		ft_lexerdel_first(lst);
		return ;
	}
	while (node && node->i != key)
	{
		prev = node;
		node = node->next;
	}
	if (node)
		prev->next = node->next;
	else
		prev->next = NULL;
	if (prev->next)
		prev->next->prev = prev;
	ft_lexerclear_one(&node);
	*lst = start;
}
/*
This function clears the entire t_lexer linked list.
It takes the address of the list pointer as an argument (**lst).
It uses a temporary variable tmp to traverse the list and free the memory for each node.
The str member of each node is freed if it is not NULL.
The memory for the node itself is freed, and tmp is updated to the next node.
The process continues until all nodes in the list are cleared.
Finally, the list pointer is set to NULL to indicate that the list is empty.
*/
void	ft_lexerclear(t_lexer **lst)
{
	t_lexer	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->str)
			free((*lst)->str);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
