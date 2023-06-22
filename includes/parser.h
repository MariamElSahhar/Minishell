/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:43:53 by szerisen          #+#    #+#             */
/*   Updated: 2023/06/22 15:52:16 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum s_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}	t_tokens;
// t_lexer includes of all of the word and tokens 
typedef struct s_lexer
{
	char			*str; // will save word if it is word or null if it is a token 
	t_tokens		token; // if it is a token if not it will be zero 
	int				i; //index
	struct s_lexer	*next; 
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_utils
{
	char					*args;
	char					**paths;
	char					**envp;
	struct s_cmds	*cmds;
	t_lexer					*lexer_list;
	char					*pwd;
	char					*old_pwd;
	int						pipes;
	int						*pid;
	bool					heredoc;
	bool					reset;
}	t_utils;

typedef struct s_cmds
{
	char			**str;
	int						(*builtin)(t_utils *, struct s_cmds *);
	int				num_redirections;
	char			*hd_file_name;
	t_lexer					*redirections;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;
