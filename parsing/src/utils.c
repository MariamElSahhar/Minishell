/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:58:40 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/11 16:51:27 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	free_double_ptr(void **ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	if (ptr)
		free(ptr);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}
