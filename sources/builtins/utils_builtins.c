/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:43:10 by szerisen          #+#    #+#             */
/*   Updated: 2023/07/06 13:59:45 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// This function updates the utils struct with the new paths
void	change_path(t_utils *utils)
{
	char	*tmp;

	tmp = ft_strdup(utils->pwd);
	free(utils->old_pwd);
	utils->old_pwd = tmp;
	free(utils->pwd);
	// This will get the current working directory. It is an inbuilt function from unistd.h
	utils->pwd = getcwd(NULL, sizeof(NULL));
}

size_t	equal_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*delete_quotes_value(char *str)
{
	char	**split_quotes;

	split_quotes = ft_split(str, '"');
	if (!split_quotes[1])
	{
		free_arr(split_quotes);
		split_quotes = ft_split(str, '\'');
	}
	free(str);
	str = ft_strjoin(split_quotes[0], split_quotes[1]);
	free_arr(split_quotes);
	return (str);
}

int	invalid_identifier(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == '[' || str[i] == ']'
		|| str[i] == '\'' || str[i] == '\"' || str[i] == ' ' || str[i] == ',' || str[i] == '.'
		|| str[i] == ':' || str[i] == '/' || str[i] == '{' || str[i] == '}' || str[i] == '+'
		|| str[i] == '^' || str[i] == '%' || str[i] == '#' || str[i] == '@' || str[i] == '!'
		|| str[i] == '~'
		|| str[i] == '-' || str[i] == '?' || str[i] == '&' || str[i] == '*')
			return (1);
	}
	return (0);
}

int	check_valid_identifier(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
		|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
		|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+'
		|| c == '^' || c == '%' || c == '#' || c == '@' || c == '!'
		|| c == '~'
		|| c == '=' || c == '-' || c == '?' || c == '&' || c == '*');
}

// "\'\"\\$ ,.:/[{]}+=-?&*^%#@!~"
