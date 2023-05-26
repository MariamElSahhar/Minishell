/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:14:20 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/26 19:28:37 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLIT_INPUT_H
# define SPLIT_INPUT_H

# include "parsing.h"

typedef struct s_word t_word;

typedef struct s_split
{
	int		cmds;
	t_word	*first;
	t_word	*last;
}	t_split;

typedef struct s_word
{
	char			*cont;
	int				index;
	int				type;
	struct s_word	*next;
	struct s_word	*prev;
}	t_word;

typedef enum e_word_type
{
	CMD,
	FLAG,
	REDIR,
	PATH,
	PIPE,
	QUOTE,
	STR,
} t_word_type;

#endif
