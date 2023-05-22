/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:08:15 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/22 18:27:49 by melsahha         ###   ########.fr       */
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

typedef struct s_utils
{
	char			*args;
	char			**envp;
	struct s_cmds	*cmds;
	char			*pwd;
	char			*old_pwd;
	int				pipes;
	int				*pid;
}	t_utils;

//  < src/main.c wc -l < src/main.c < src/input_utils.c > out.txt
// cmd.command = wc
// cmd.args = {-lns, ...}
// wc -l | cd parsing/ | ls
typedef struct s_cmds
{
	/* char			**str;
		//  < src/main.c wc -l < src/main.c < src/input_utils.c > out.txt
		// command + flag/path */
	char			*command;
		// wc echo
	char			**args; //flags or path
		// -l -n
	int				num_output;
		// 1
	t_redir			*redirections;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

typedef struct s_redir
{
	int		type;
	char	*path;
	int		fd;
	t_redir	*next;
	t_redir	*prev;
} t_redir;

typedef enum e_redir
{
	APPEND,
	WRITE,
	HEREDOC,
	INPUT,
}	t_redir;

t_utils	*split_input(char *input);
void	free_double_ptr(void **ptr);
int		check_input(char *input);
int		is_space(char c);
int		is_quote(char c);
int		is_symbol(char c);
int		open_quotes(char *input);
void	skip_quotes(int *i, char *input);


#endif
