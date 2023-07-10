/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:56:27 by szerisen          #+#    #+#             */
/*   Updated: 2023/07/10 18:18:02 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
// # include "parser.h"
# include "utils.h"
# include "error.h"
// # include "lexer.h"
# include "color.h"
# include "builtins.h"
# include "executor.h"
# include "parsing.h"

# include <sys/types.h>
# include <sys/wait.h>


int		parse_envp(t_utils *utils);
int		find_pwd(t_utils *utils);
int		reset_utils(t_utils *utils);
void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	init_signals(void);
void	free_utils(t_utils *utils);

char	*delete_quotes_value(char *str);
char	*delete_quotes(char *str, char c);
char	*delete_quotes_export(char *str, char c);


//builtins
int		(*builtin_arr(char *str))(t_utils *utils, t_cmds *cmds);
typedef struct s_gvar
{
	int	error_code;
	int	stop_heredoc;
	int	in_cmd;
	int	in_heredoc;
}	t_gvar;

t_gvar	g_global;

#endif
