/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:56:37 by szerisen          #+#    #+#             */
/*   Updated: 2023/07/06 14:22:39 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "parsing.h"
# include "minishell.h"

// utils
int				count_quotes(char *line);
int				implement_utils(t_utils *utils);
char			**ft_arrdup(char **arr);

void				minishell_loop(t_utils *utils, char **envp);
void	free_double_ptr(void **ptr);

/* //t_cmds_utils
t_cmds	*ft_cmdsnew(char **str,
					int num_redirections, t_lexer *redirections);
void			ft_cmdsadd_back(t_cmds **lst, t_cmds *new);
void			ft_cmds_rm_first(t_cmds **lst);
void			ft_cmdsclear(t_cmds **lst);
t_cmds	*ft_cmdsfirst(t_cmds *map);

//t_lexer_utils
t_lexer			*ft_lexernew(char *str, int token);
void			ft_lexeradd_back(t_lexer **lst, t_lexer *new);
void			ft_lexerdelone(t_lexer **lst, int i);
void			ft_lexerclear(t_lexer **lst);

//
int				token_reader(t_utils *utils);
int				add_node(char *str, t_tokens token, t_lexer **lexer_list);
t_tokens		check_token(int c);
int				handle_token(char *str, int i, t_lexer **lexer_list); */

#endif
