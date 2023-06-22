/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:58:27 by melsahha          #+#    #+#             */
/*   Updated: 2023/06/21 16:53:07 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	free_split(t_split *split)
{
	t_word	*del;
	t_word	*ptr;

	ptr = split->first;
	while (ptr)
	{
		del = ptr;
		ptr = ptr->next;
		free(del);
	}
	free(split);
}

int	split_words(char *input, t_split *split)
{
	int	i;

	i = 0;
	while (input[i])
	{
		skip_space(input, &i);
		if (input[i])
		{
			if (!define_word(input, &i, split))
			{
				free_split(split);
				return (0);
			}
		}
	}
	return (1);
}

t_split	*split_input(char *input)
{
	t_split	*split;

	split = (t_split *)ft_calloc(1, sizeof(t_split));
	if (!split || !input)
		return (0);
	if (!split_words(input, split))
		return (0);
	if (!check_split(split))
	{
		printf("check split error\n");
		free_split(split);
		return (0);
	}
	if (!expand_env(split) || !expand_split(split))
	{
		printf("expand error\n");
		return (0);
	}
	sort_split(split);
	return (split);
}

void	sort_split(t_split *split)
{
	t_word	*ptr;

	ptr = split->first;
	if (ptr && ptr->type == STR)
		ptr->type = CMD;
	while (ptr)
	{
		if (ptr->prev && ptr->type == STR && ptr->prev->type == PIPE)
			ptr->type = CMD;
		else if (ptr->prev && ptr->prev->type == REDIR)
			ptr->type = PATH;
		else if (ptr->prev && ptr->type == STR && ptr->prev->type == PATH)
			ptr->type = CMD;
		else if (ptr->type == STR)
			ptr->type = ARG;
		ptr = ptr->next;
	}
}
