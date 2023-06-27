/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:03:39 by melsahha          #+#    #+#             */
/*   Updated: 2023/06/27 14:10:22 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// returns 1 if - is followed by nothing
static int	empty_flag(t_word *flag)
{
	char	*str;
	char	quote;
	int		i;

	str = flag->cont;
	if (ft_strlen(str) == 1)
		return (1);
	i = 1;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			quote = str[i++];
			skip_space(str, &i);
			if (str[i] && str[i] == quote)
				return (1);
			while (str[i] && str[i] != quote)
				i++;
			i++;
		}
		while (str[i] && !is_quote(str[i]))
			i++;
	}
	return (0);
}

//checks for issues in input structure
int	check_split(t_split *split)
{
	t_word	*ptr;

	ptr = split->first;
	if (ptr
		&& (ptr->type == PIPE || ptr->type == FLAG
			|| split->last->type == PIPE || split->last->type == REDIR))
		return (!parser_error(ptr));
	while (ptr)
	{
		if (ptr->type == REDIR
			&& (ptr->next && (ptr->next->type == REDIR
					|| ptr->next->type == PIPE)))
			return (!parser_error(ptr));
		if (ptr->type == FLAG && !(ptr->prev && ptr->prev->type == REDIR)
			&& empty_flag(ptr))
			return (!parser_error(ptr));
		if (ptr->type == PIPE
			&& (ptr->next && (ptr->next->type == PIPE
					|| ptr->next->type == FLAG)))
			return (!parser_error(ptr));
		ptr = ptr->next;
	}
	return (1);
}
