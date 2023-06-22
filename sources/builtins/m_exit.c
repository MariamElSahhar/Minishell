/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:42:56 by szerisen          #+#    #+#             */
/*   Updated: 2023/05/30 20:12:20 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <signal.h>

void	free_utils(t_utils *utils)
{
	// free_arr function will free the double pointer array
	free_arr(utils->paths);
	free_arr(utils->envp);
	free(utils->args);
	ft_cmdsclear(&utils->cmds);
	free(utils->pwd);
	free(utils->old_pwd);
	if (utils->pipes)
		free(utils->pid);
}

int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	determine_exit_code(char **str)
{
	int	exit_code;

	// if exit is passed without any argument it returns 0
	if (!str[1])
		exit_code = 0;
	// checks if the second argument (str[1]) after the "exit" command is a valid numeric value.
	else if (is_str_digit(str[1]))
		exit_code = ft_atoi(str[1]);
	else
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(str[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_code = 255;
	}
	free_arr(str);
	exit(exit_code);
}

int	m_exit(t_utils *utils, t_cmds *cmds)
{
	char	**str;

	ft_putendl_fd("exit", STDERR_FILENO);
	// This check if the exit function has more that two arguments
	if (cmds->str[1] && cmds->str[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	str = ft_arrdup(cmds->str);
	// free before you determine the exit_code and exit  
	free_utils(utils);
	determine_exit_code(str);
	return (EXIT_SUCCESS);
}
