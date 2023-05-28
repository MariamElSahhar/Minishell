/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 11:39:28 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/28 11:58:28 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	expand_env_str(t_word *word)
{
	int		i;
	int		len;
	char	*var;

	if (!ft_strchr(word->cont, '$'))
		return (1);
	i = 0;
	if (word->type == FLAG)
		i++;
	while (word->cont[i])
	{
		len = 0;
		if (word->cont[i] == '$')
		{
			while (word->cont[++i] && !is_space(word->cont[i])
				&& !is_quote(word->cont[i]) && word->cont[i] != '$')
				len++;
			var = ft_calloc(len + 1, sizeof(char));
			//FINISH THIS
		}

	}
	return (1);
}

int	expand_env(t_split *split)
{
	t_word	*ptr;
	int		success;

	ptr = split->first;
	while (ptr)
	{
		if (ptr->type == STR || ptr->type == CMD || ptr->type == FLAG || ptr->type == PATH)
			success = expand_env_str(ptr);
		// else if (ptr->type == QUOTE && ptr->cont[0] == "\"")
		// 	success = expand_var_quote(ptr);
		if (!success)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}
