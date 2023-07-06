/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:08:27 by szerisen          #+#    #+#             */
/*   Updated: 2023/07/06 14:48:37 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// get's hold of the present working directory and old pwd from the copied envp (utils->envp)
/*
This function takes a t_utils structure (which likely holds some utility variables) as a parameter.
It iterates through the utils->envp array, which is assumed to be an array of strings containing environment variables.
Inside the loop, it checks each element of utils->envp to find the environment variables for "PWD" and "OLDPWD" (present working directory and old working directory, respectively).
If a matching environment variable is found, it extracts the value part (after the equals sign) using ft_substr and assigns it to utils->pwd or utils->old_pwd.
Finally, the function returns 1, indicating success.
*/
int	find_pwd(t_utils *utils)
{
	int	i;

	i = 0;
	while (utils->envp[i])
	{
		if (!ft_strncmp(utils->envp[i], "PWD=", 4))
			utils->pwd = ft_substr(utils->envp[i],
					4, ft_strlen(utils->envp[i]) - 4);
		if (!ft_strncmp(utils->envp[i], "OLDPWD=", 7))
			utils->old_pwd = ft_substr(utils->envp[i],
					7, ft_strlen(utils->envp[i]) - 7);
		i++;
	}
	return (1);
}
/*
This function takes a char** parameter called envp, which is assumed to be an array of strings containing
environment variables. It iterates through the envp array, similar to the previous function.
Inside the loop, it looks for the environment variable "PATH" and returns its corresponding value
(the part after the equals sign) using ft_substr. If the "PATH" environment variable is not found, it returns
an empty string obtained by duplicating the null terminator character.
Note: It assumes that ft_substr is a custom function to extract substrings.
*/
char	*find_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
		i++;
	}
	return (ft_strdup("\0"));
}
/*
This function takes a t_utils structure (likely containing utility variables) as a parameter.
It calls the find_path function, passing utils->envp as an argument, to obtain the "PATH" environment variable value.
The returned value is stored in path_from_envp.
It then splits path_from_envp using ':' as the delimiter to obtain individual paths, and stores them in utils->paths
using ft_split. After storing the paths, it frees the memory allocated for path_from_envp.
It then iterates through each path in utils->paths.
For each path, it checks if the last character is not a slash ('/').
If it's not a slash, it appends a slash to the path using ft_strjoin and assigns the updated path to utils->paths[i].
Finally, the function returns EXIT_SUCCESS, indicating successful parsing of the environment variables.
*/
int	parse_envp(t_utils *utils)
{
	char	*path_from_envp;
	int		i;
	char	*tmp;

	path_from_envp = find_path(utils->envp);
	utils->paths = ft_split(path_from_envp, ':');
	free(path_from_envp);
	i = 0;
	while (utils->paths[i])
	{
		if (ft_strncmp(&utils->paths[i][ft_strlen(utils->paths[i]) - 1],
			"/", 1) != 0)
		{
			tmp = ft_strjoin(utils->paths[i], "/");
			free(utils->paths[i]);
			utils->paths[i] = tmp;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
