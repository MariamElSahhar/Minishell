/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:08:15 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/11 16:50:36 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef enum e_redirect
{
	INPUT,
	OUTPUT,
	APPEND,
}	t_redirect;

typedef struct s_command
{
	const char	*pathname;
	const char	**argv;
	const char	*envp[];
}	t_command;

typedef struct s_input
{
	int			pipes;
	t_command	*command_list;
}	t_input;

char	**split_input(char const *s);
void	free_double_ptr(void **ptr);
int		check_input(char *input);
int		is_space(char c);
int		is_quote(char c);



#endif
