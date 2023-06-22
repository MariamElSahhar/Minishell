/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:42:59 by szerisen          #+#    #+#             */
/*   Updated: 2023/05/30 20:11:41 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "builtins.h"

int	variable_exist(t_utils *utils, char *str)
{
	int	i;

	i = 0;
	if (str[equal_sign(str)] == '\"')
		delete_quotes(str, '\"');
	if (str[equal_sign(str)] == '\'')
		delete_quotes(str, '\'');
	while (utils->envp[i])
	{
		if (ft_strncmp(utils->envp[i],
				str, equal_sign(utils->envp[i])) == 0)
		{
			free(utils->envp[i]);
			utils->envp[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_parameter(char *str)
{
	int	i;

	i = 0;
	//verifies that a variable is not a digit if it is returns an error not valid identifier.
	if (ft_isdigit(str[0]))
		return (export_error(str));
	if (equal_sign(str) == 0)	
		return (EXIT_FAILURE);
	if (str[0] == '=')
		return (export_error(str));
	while (str[i] != '=')
	{
		if (check_valid_identifier(str[i]))
			return (export_error(str));
		i++;
	}
	return (EXIT_SUCCESS);
}
/* copies the existing environment variables (arr) and adding a new variable (str) at the end of the copied list */
char	**whileloop_add_var(char **arr, char **rtn, char *str)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (arr[i + 1] == NULL)
		{
			rtn[i] = ft_strdup(str);
			rtn[i + 1] = ft_strdup(arr[i]);
		}
		else
			rtn[i] = ft_strdup(arr[i]);
		if (rtn[i] == NULL)
		{
			free_arr(rtn);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}

/*
it takes arr and adds str and return rtn which is composed of both
it allocates memory for the additional variable and return it
*/
char	**add_var(char **arr, char *str)
{
	char	**rtn;
	size_t	i;

	i = 0;
	if (str[equal_sign(str)] == '\"')
		delete_quotes(str, '\"');
	if (str[equal_sign(str)] == '\'')
		delete_quotes(str, '\'');
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 2);
	if (!rtn)
		return (NULL);
	i = 0;
	whileloop_add_var(arr, rtn, str);
	return (rtn);
}

int	m_export(t_utils *utils, t_cmds *cmds)
{
	char	**tmp;
	int		i;

	i = 1;
	// if the command export is passed without any arguments we just return env (acts as env)
	if (!cmds->str[1] || cmds->str[1][0] == '\0')
		mini_env(utils, cmds);
	else
	{
		// if there is a second argument it will go inside the while loop
		// variable exist will check if str exist in env variable 
		while (cmds->str[i])
		{
			if (check_parameter(cmds->str[i]) == 0
				&& variable_exist(utils, cmds->str[i]) == 0)
			{
				if (cmds->str[i])
				{
					tmp = add_var(utils->envp, cmds->str[i]);
					free_arr(utils->envp);
					utils->envp = tmp;
				}
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

/*
the function calls ft_strlcpy to copy the remaining part of the string str (after the consecutive occurrences of c) 
*/
// Supposed to be added in utils file in parser folder

char	*delete_quotes(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], strlen(str) - i);
		}
		i++;
	}
	return (str);
}