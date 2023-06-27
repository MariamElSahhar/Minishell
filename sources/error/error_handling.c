/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:04:46 by szerisen          #+#    #+#             */
/*   Updated: 2023/06/27 14:18:46 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief
 * Finds corresponding error and frees args;
 * @param error
 * Number of related error:
 * 0 = If there is no string following a redirection or a pipe.
 * @param utils
 */
int	ft_error(int error, t_utils *utils)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error == 0)
		ft_putstr_fd("syntax error near unexpected token 'newline'\n",
			STDERR_FILENO);
	else if (error == 1)
		ft_putstr_fd("memory error: unable to assign memory\n", STDERR_FILENO);
	else if (error == 2)
		ft_putstr_fd("syntax error: unable to locate closing quotation\n",
			STDERR_FILENO);
	else if (error == 3)
		ft_putstr_fd("Parser problem\n", STDERR_FILENO);
	else if (error == 4)
		ft_putstr_fd("Failed to create pipe\n", STDERR_FILENO);
	else if (error == 5)
		ft_putstr_fd("Failed to fork\n", STDERR_FILENO);
	else if (error == 6)
		ft_putstr_fd("outfile: Error\n", STDERR_FILENO);
	else if (error == 7)
		ft_putstr_fd("infile: No such file or directory\n", STDERR_FILENO);
	else if (error == 8)
		ft_putendl_fd("Path does not exist", STDERR_FILENO);
	else if (error == 9)
		ft_putendl_fd("Path does not exist", STDERR_FILENO);
	if (utils)
		reset_utils(utils);
	return (EXIT_FAILURE);
}

int	parser_error(t_word *ptr)
{
	if (ptr->type == PIPE)
		token_error(0, ERR_PIPE);
	else if (ptr->type == REDIR && ft_strlen(ptr->cont) == 1)
	{
		if (ptr->cont[0] == '>')
			token_error(0, ERR_G);
		else if (ptr->cont[0] == '<')
			token_error(0, ERR_L);
	}
	else if (ptr->type == REDIR && ft_strlen(ptr->cont) == 2)
	{
		if (ptr->cont[0] == '>')
			token_error(0, ERR_GG);
		else if (ptr->cont[0] == '<')
			token_error(0, ERR_LL);
	}
	return (EXIT_FAILURE);
}

int	invalid_token_error(char *c)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDERR_FILENO);
	ft_putstr_fd(c, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	token_error(t_utils *utils, int code)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDERR_FILENO);
	if (code == ERR_G)
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	else if (code == ERR_GG)
		ft_putstr_fd("'>>'\n", STDERR_FILENO);
	else if (code == ERR_L)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	else if (code == ERR_LL)
		ft_putstr_fd("'<<'\n", STDERR_FILENO);
	else if (code == ERR_PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	else
		ft_putstr_fd("\n", STDERR_FILENO);
	if (utils)
		reset_utils(utils);
	return (EXIT_FAILURE);
}
