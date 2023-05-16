/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:08:15 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/16 18:46:10 by melsahha         ###   ########.fr       */
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
	char			**str;
		//  < src/main.c wc -l < src/main.c < src/input_utils.c > out.txt
		// command + flag/path
	char			*command;
		// wc echo
	char			**args; //flags or path
		// -l -n
	int				num_output;
		// 1
	char			**out_file_name;
		// out.txt
	int				*append;
		// true / false
	char			*in_file_name;
		// src/input_utils.c / NULL
	bool			heredoc;
		// true / false
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

t_utils	*split_input(char *input);
void	free_double_ptr(void **ptr);
int		check_input(char *input);
int		is_space(char c);
int		is_quote(char c);
int		open_quotes(char *input);
void	in_quotes(int *i, char *input);


#endif
