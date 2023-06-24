/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 11:39:28 by melsahha          #+#    #+#             */
/*   Updated: 2023/06/24 15:21:15 by melsahha         ###   ########.fr       */
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
		return (0);
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

// returns value of the variable var in utils.envp
char	*ft_getenv(char *var, t_utils *utils)
{
	int		i;
	char	*value;
	char	c;

	i = -1;
	value = var;
	c = '=';
	while (utils->envp[++i])
	{
		if (!ft_strncmp(var, utils->envp[i], ft_strlen(var)))
		{
			value = ft_strtrim(ft_strchr(utils->envp[i], '='), &c);
			return (value);
		}
	}
	return (0);
}

// finds location of env and allocates memory for replacement
int	found_env(char *str, int *i, t_word *word, t_utils *utils)
{
	int		len;
	char	*var;
	int		j;
	char	*exp;

	len = 0;
	j = (*i);
	while (str[++j] && !is_space(str[j])
		&& !is_quote(str[j]) && str[j] != '$')
		len++;
	var = (char *)ft_calloc(len + 1, sizeof(char));
	if (!var)
		return (0);
	j = 0;
	(*i)++;
	while (j < len)
		var[j++] = str[(*i)++];
	exp = ft_getenv(var, utils);
	if (!exp)
		return (0);
	word->cont = replace_env(str, i, exp, len);
	free(var);
	if (!word->cont)
		return (0);
	return (1);
}

// expands env variables except in quotes
int	expand_env_str(t_word *word, t_utils *utils)
{
	int		i;

	if (!ft_strchr(word->cont, '$'))
		return (1);
	i = 0;
	if (word->type == FLAG)
		i = 1;
	while (word->cont[i])
	{
		if (word->cont[i] == '$')
		{
			if (word->cont[i + 1] == '?')
			{
				i = i + 2;
				word->cont = replace_env(word->cont, &i, ft_itoa(g_global.error_code), 1);
			}
			else if (!found_env(word->cont, &i, word, utils))
				return (0);
			i = 0;
		}
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
		if (word->cont[i] == '\"')
			i++;
		else if (word->cont[i] == '\'')
			skip_quotes(&i, word->cont);
		else if (word->cont[i] == '$')
		{
			if (!found_env(word->cont, &i, word, utils))
				return (0);
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
			|| ptr->type == FLAG || ptr->type == PATH)
			success = expand_env_str(ptr, utils);
		else if (ptr->type == QUOTE)
			success = expand_var_quote(ptr, utils);
		if (!success)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}
