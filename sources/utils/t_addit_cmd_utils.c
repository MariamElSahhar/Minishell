/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_addit_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:09:56 by szerisen          #+#    #+#             */
/*   Updated: 2023/06/23 16:28:42 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
This function creates a new node for the t_cmds linked list.
It takes three arguments: str, which represents an array of strings (command and arguments), num_redirections, which represents
 the number of redirections associated with the command, and redirections, which is a linked list of tokens representing the redirections.
It allocates memory for a new t_cmds structure using malloc.
If the allocation fails, it returns NULL.
Otherwise, it initializes the str, num_redirections, and redirections members of the new node with the provided values.
The builtin member is set by calling the builtin_arr function with str[0], which returns the appropriate enum value for the given command.
The hd_file_name member is initialized to NULL.
The next and prev pointers are initialized to NULL.
Finally, the function returns the newly created node.
*/
t_cmds	*ft_cmdsnew(char **str,
	int num_redirections, t_lexer *redirections)
{
	t_cmds	*new_element;

	new_element = (t_cmds *)malloc(sizeof(t_cmds));
	if (!new_element)
		return (0);
	new_element->str = str;
	new_element->builtin = builtin_arr(str[0]);
	new_element->hd_file_name = NULL;
	new_element->num_redirections = num_redirections;
	new_element->redirections = redirections;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}
/*
This function adds a new node to the end of the t_cmds linked list.
It takes two arguments: the address of the list pointer (**lst) and the new node to be added (*new).
It uses a temporary variable tmp to traverse the list and find the last node.
If the list pointer is NULL, meaning the list is empty, the new node becomes the first node.
Otherwise, it iterates through the list until it reaches the last node (where tmp->next is NULL).
It assigns the next pointer of the last node to the new node and updates the prev pointer of the new node to point to the last node.
By doing so, the new node becomes the last node in the list.
If the list was empty, the new node is now the first and last node.
Finally, the function returns, and the list is updated accordingly.
*/
void	ft_cmdsadd_back(t_cmds **lst, t_cmds *new)
{
	t_cmds	*tmp;

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
/*
This function removes the first node from the t_cmds linked list.
It takes the address of the list pointer (**lst).
It assigns the next node of the first node to a temporary variable tmp.
It clears the redirections associated with the first node using the ft_lexerclear function.
It frees the memory allocated for the first node using free.
Finally, it updates the list pointer to the next node (*lst = tmp).
*/
void	ft_cmds_rm_first(t_cmds **lst)
{
	t_cmds	*tmp;

	if (!*lst)
		return ;
	tmp = (*lst)->next;
	ft_lexerclear(&(*lst)->redirections);
	free(*lst);
	*lst = tmp;
}
/*
This function clears the entire t_cmds linked list, freeing all the memory associated with each node.
It takes the address of the list pointer (**lst).
It uses a temporary variable tmp to traverse the list and a temporary variable redirections_tmp to hold the redirections of each node.
It iterates through the list and for each node:
It assigns the next node to tmp.
It clears the redirections using the ft_lexerclear function on redirections_tmp.
It frees the memory allocated for the command and arguments array (str).
It frees the memory allocated for the here-document file name (hd_file_name).
It frees the memory allocated for the node itself.
It updates the list pointer to the next node (*lst = tmp).
Finally, it sets the list pointer to NULL.
*/
void	ft_cmdsclear(t_cmds **lst)
{
	t_cmds	*tmp;
	t_lexer			*redirections_tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		redirections_tmp = (*lst)->redirections;
		ft_lexerclear(&redirections_tmp);
		if ((*lst)->str)
			free_arr((*lst)->str);
		if ((*lst)->hd_file_name)
			free((*lst)->hd_file_name);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
/*
This function returns the first node of the t_cmds linked list.
It takes the head of the list (map) as the argument.
It iterates through the list by following the prev pointers until it reaches the first node (where map->prev is NULL).
If the list is empty, it returns NULL.
Otherwise, it returns the pointer to the first node.
*/
t_cmds	*ft_cmdsfirst(t_cmds *map)
{
	int	i;

	i = 0;
	if (!map)
		return (NULL);
	while (map->prev != NULL)
	{
		map = map->prev;
		i++;
	}
	return (map);
}
