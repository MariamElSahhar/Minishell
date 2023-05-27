/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:03:39 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/27 16:07:52 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

static int	empty_flag(t_word *flag)
{
	char	*str;
	char	quote;
	int		i;

	str = flag->cont;
	if (ft_strlen(str) == 1)
		return (1);
	if (str[1] && (str[1] == '|' || str[1] == '>' || str[1] == '<'))
		return (1);
	i = 1;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			quote = str[i];
			i++;
			if (str[i] && (is_space(str[i]) || str[i] == quote))
				return (1);
		}
		while (str[i] && !is_quote(str[i]))
			i++;
	}
	return (0);
}

int	check_split(t_split *split)
{
	t_word	*ptr;

	ptr = split->first;
	if (ptr &&
		(ptr->type == PIPE || ptr->type == FLAG ||
		split->last->type == PIPE || split->last->type == REDIR))
		return (0);
	while (ptr)
	{
		if (ptr->type == REDIR &&
			(ptr->next && (ptr->next->type == REDIR || ptr->next->type == PIPE)))
				return (0);
		if(ptr->type == FLAG &&
			(empty_flag(ptr) ||  (ptr->next && (ptr->next->type == REDIR || ptr->next->type == PIPE))))
				return (0);
		if (ptr->type == PIPE &&
			(ptr->next && (ptr->next->type == PIPE || ptr->next->type == FLAG)))
				return (0);
		ptr = ptr->next;
	}
	return (1);
}
