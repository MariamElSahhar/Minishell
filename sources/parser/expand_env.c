/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 11:39:28 by melsahha          #+#    #+#             */
/*   Updated: 2023/07/06 14:08:36 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// replaces the environment var with its value
char	*replace_env(char *str, int *i, char *exp, int len)
{
	char	*full;
	int		j;
	int		k;

	full = (char *)ft_calloc((ft_strlen(str) - len)
			+ ft_strlen(exp) + 2, sizeof(char));
	if (!full)
	{
		ft_error(1, 0);
		return (0);
	}
	j = -1;
	k = (*i) - len - 1;
	while (++j < k)
		full[j] = str[j];
	k = 0;
	while (k < (int)ft_strlen(exp))
		full[j++] = exp[k++];
	k = (*i);
	while (k < (int)ft_strlen(str))
		full[j++] = str[k++];
	free(str);
	return (full);
}


// finds location of env and allocates memory for replacement
int	found_env(char *old, int *i, t_word *word, t_utils *utils)
{
	int		len;
	char	*var;
	int		j;
	char	*env;

	// printf("old: %s\n", old);
	len = 0;
	j = (*i);
	while (old[++j] && !is_space(old[j]) && old[j] != '$'
		&& !check_valid_identifier(old[j]))
		len++;
	var = (char *)ft_calloc(len + 1, sizeof(char));
	if (!var)
		return (!ft_error(1, 0));
	j = 0;
	(*i)++;
	while (j < len)
		var[j++] = old[(*i)++];
	env = ft_getenv(var, utils);
	if (!env)
		return (0);
	word->cont = replace_env(old, i, env, len);
	// printf("new: %s\n", word->cont);
	free(var);
	if (!word->cont)
		return (0);
	*i = 0;
	return (1);
}

// expands env variables except in quotes
int	expand_env_str(t_word *word, t_utils *utils)
{
	int		i;

	if (!ft_strchr(word->cont, '$'))
		return (1);
	i = 0;
	while (word->cont[i])
	{
		if (word->cont[i] == '$' && word->cont[i + 1] && word->cont[i + 1] == '?')
		{
			i = i + 2;
			word->cont = replace_env(word->cont, &i, ft_itoa(g_global.error_code), 1);
			if (!word->cont)
				return (0);
			i = 0;
		}
		else if (word->cont[i] == '$' && word->cont[i + 1]
				&& check_valid_identifier(word->cont[i + 1]))
			i = i + 2;
		else if (word->cont[i] == '$' && word->cont[i + 1]
				&& !found_env(word->cont, &i, word, utils))
				return (0);
		else
			i++;
	}
	return (1);
}

// expands env variables in double quotes
int	expand_var_quote(t_word *word, t_utils *utils)
{
	int	i;

	if (!ft_strchr(word->cont, '$'))
		return (1);
	i = 0;
	while (word->cont[i])
	{
		if (word->cont[i] == '$' && !found_env(word->cont, &i, word, utils))
			return (0);
		else if (word->cont[i] == '\'')
			skip_quotes(&i, word->cont);
		else if (word->cont[i] == '\"')
		{
			i++;
			while (word->cont[i] && word->cont[i] != '\"')
			{
				if (word->cont[i] == '$')
				{
					found_env(word->cont, &i, word, utils);
					break;
				}
				else
					i++;
			}
			if (word->cont[i] == '\"')
				i++;
		}
		else
			i++;
	}
	return (1);
}

// redirects tokens to expanders
int	expand_env(t_split *split, t_utils *utils)
{
	t_word	*ptr;
	int		success;

	ptr = split->first;
	while (ptr)
	{
		if (ptr->type == STR || ptr->type == CMD
			|| ptr->type == ARG || ptr->type == PATH)
			success = expand_env_str(ptr, utils);
		else if (ptr->type == QUOTE)
			success = expand_var_quote(ptr, utils);
		if (!success)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}
