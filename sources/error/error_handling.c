/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:04:46 by szerisen          #+#    #+#             */
/*   Updated: 2023/06/23 17:28:12 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* void	parser_error(int error, t_utils *utils, t_lexer *lexer_list)
{
	ft_lexerclear(&lexer_list);
	ft_error(error, utils);
} */

int	parser_token_error(t_utils *utils, int code)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDERR_FILENO);
	if (code == ERR_SEMICOL)
		ft_putstr_fd("';'\n", STDERR_FILENO);
	else if (code == ERR_BACKSLASH)
		ft_putstr_fd("'\\'\n", STDERR_FILENO);
	if (utils)
		reset_utils(utils);
	return (EXIT_FAILURE);
}

int	parser_double_token_error(t_utils *utils, int code)
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
	else if (code == ERR_PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	else
		ft_putstr_fd("\n", STDERR_FILENO);
	if (utils)
		reset_utils(utils);
	return (EXIT_FAILURE);
}

/* int	parser_double_token_error(t_utils *utils, t_lexer *lexer_list,
	t_tokens token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDERR_FILENO);
	if (token == GREAT)
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	else if (token == GREAT_GREAT)
		ft_putstr_fd("'>>'\n", STDERR_FILENO);
	else if (token == LESS)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	else if (token == LESS_LESS)
		ft_putstr_fd("'<<'\n", STDERR_FILENO);
	else if (token == PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	else
		ft_putstr_fd("\n", STDERR_FILENO);
	ft_lexerclear(&lexer_list);
	reset_utils(utils);
	return (EXIT_FAILURE);
}
 */
