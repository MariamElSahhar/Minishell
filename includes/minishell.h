/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:56:27 by szerisen          #+#    #+#             */
/*   Updated: 2023/05/10 17:56:28 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libraries/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "parser.h"
# include "utils.h"
# include "color.h"
# include "builtins.h"
# include "executer.h"


typedef struct s_gvar
{
	int	error_code;
	int	stop_heredoc;
	int	in_cmd;
	int	in_heredoc;
}	t_gvar;

t_gvar	g_global;

#endif