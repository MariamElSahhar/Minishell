/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:58:27 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/26 19:42:00 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

static int	empty_flag(t_word *flag)
{
	char	*str;
	char	quote;
	int		i;

	str = flag->cont;
	if (str[1] && is_space(str[1]))
		return (1);
	if (str[1] && (str[1] == '|' || str[1] == '>' || str[1] == '<'))
		return (1);
	if (str[1] && is_quote(str[1]))
	{
		quote = str[1];
		i = 1;
		skip_space(str, &i);
		if (str[i] && str[i] == quote)
			return (1);
	}
	return (0);
}

int	check_split(t_split *split)
{
	t_word	*ptr;

	ptr = split->first;
	if (ptr && (ptr->type == PIPE || ptr->type == FLAG))
		return (0);
	while (ptr)
	{
		if (ptr->type == REDIR)
		{
			if (ptr->next && (ptr->next->type == REDIR || ptr->next->type == PIPE))
				return (0);
		}
		if(ptr->type == FLAG)
		{
			if (empty_flag(ptr) ||  (ptr->next && (ptr->next->type == REDIR || ptr->next->type == PIPE)))
				return (0);
		}
		if (ptr->type == PIPE)
		{
			if (ptr->next && (ptr->next->type == PIPE || ptr->next->type == FLAG))
				return (0);
		}
		ptr = ptr->next;
	}
	return (1);
}
