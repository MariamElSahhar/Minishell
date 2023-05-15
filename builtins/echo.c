/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:42:50 by szerisen          #+#    #+#             */
/*   Updated: 2023/05/10 17:42:51 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_lines(int i, char **str, int out)
{
	while (str[i])
	{
		ft_putstr_fd(str[i++], out);
		if (str[i])
			ft_putchar_fd(' ', out);
	}
}

int	echo(t_utils *utils, t_cmds *cmds)
{
	int		i;
	int		j;
	bool	n_option;

	i = 1;
	n_option = false;
	(void) utils;
	while (cmds->str[i] && cmds->str[i][0] == '-'
		&& cmds->str[i][1] == 'n')
	{
		j = 1;
		while (cmds->str[i][j] == 'n')
			j++;
		if (cmds->str[i][j] == '\0')
			n_option = true;
		else
			break ;
		i++;
	}
	print_lines(i, cmds->str, STDOUT_FILENO);
	if (n_option == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
