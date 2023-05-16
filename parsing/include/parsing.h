/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:08:15 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/16 11:55:04 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_utils
{
	char			*args;
	char			**paths;
	char			**envp;
	struct s_cmds	*cmds;
	char			*pwd;
	char			*old_pwd;
	int				pipes;
	int				*pid;
	bool			heredoc;
	bool			reset;
}	t_utils;

typedef struct s_cmds
{
	char			**str;
	int				num_redirections;
	char			*hd_file_name;
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
