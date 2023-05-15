/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:42:44 by szerisen          #+#    #+#             */
/*   Updated: 2023/05/15 20:09:37 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	(*builtin_arr(char *str))(t_utils *utils, t_cmds *cmds)
{
	static void	*builtins[7][2] = {
	{"echo", echo},
	{"cd", cd},
	{"pwd", pwd},
	{"export", export},
	{"unset", unset},
	{"env", env},
	{"exit", mini_exit}
	};
	int			i;

	i = 0;
	while (i < 7)
	{
		if (str)
		{
			if (!ft_strncmp(builtins[i][0], str, ft_strlen((builtins[i][0]))))
				return (builtins[i][1]);
		}
		i++;
	}
	return (NULL);
}
