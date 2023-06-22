/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:56:27 by szerisen          #+#    #+#             */
/*   Updated: 2023/05/29 19:47:57 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
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
# include "error.h"
# include "lexer.h"
# include "color.h"
# include "builtins.h"
# include "executer.h"

int		parse_envp(t_utils *utils);
int		find_pwd(t_utils *utils);
int		reset_utils(t_utils *utils);
void	init_stri(int i, int j, t_utils *utils);
char	**expander(t_utils *utils, char **str);
char	*expander_str(t_utils *utils, char *str);
size_t	dollar_sign(char *str);
char	*char_to_str(char c);
int		after_dol_lenght(char *str, int j);
void	free_things(char *tmp2, t_utils *utils, int i);
void	print_parser(t_cmds cmdss);
char	*delete_quotes_value(char *str);
void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	init_signals(void);
char	*delete_quotes(char *str, char c);
char	*delete_quotes_export(char *str, char c);
int		question_mark(char **tmp);

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