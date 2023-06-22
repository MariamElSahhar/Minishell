/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:08:15 by melsahha          #+#    #+#             */
/*   Updated: 2023/06/22 10:22:03 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include "split.h"

# define CLEAR_SCREEN_SEQ "\033[2J\033[H"


typedef struct s_cmds	t_cmds;
typedef struct s_redir	t_redir;

typedef struct s_utils
{
	struct s_cmds	*cmds;
	char			*input;
	char			**envp;
	char			*pwd;
	char			*old_pwd;
	int				pipes;
	int				*pid;
}	t_utils;

typedef struct s_cmds
{
	char			*command;
	char			**args;
	t_redir			*redirections;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

typedef struct s_redir
{
	int				type;
	char			*path;
	int				fd;
	struct s_redir	*next;
	struct s_redir	*prev;
}	t_redir;

typedef enum e_redir
{
	IGNORE,
	OPEN,
	APPEND,
	WRITE,
	INPUT,
	HEREDOC,
}	t_redir_type;

void	free_double_ptr(void **ptr);
int		is_space(char c);
int		is_quote(char c);
int		is_symbol(char c);
void	skip_quotes(int *i, char *input);
void	skip_space(char *input, int *j);
void	push_cmd(t_utils *utils, t_cmds *cmd);

int		check_input(char *input);
t_utils	*sort_tokens(t_split *split);
void	end_of_flag(char *input, int *i);
void	last_in_redir(t_cmds *cmd);
void	last_out_redir(t_cmds *cmd);
void	sort_redir(t_word *ptr, t_redir *redir);

#endif
