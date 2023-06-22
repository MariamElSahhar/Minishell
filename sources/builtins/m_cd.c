/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:42:47 by szerisen          #+#    #+#             */
/*   Updated: 2023/05/30 20:12:36 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// #include "minishell.h"
#include "builtins.h"

char	*find_path_ret(char *str, t_utils *utils)
{
	int	i;

	i = 0;
	while (utils->envp[i])
	{
		if (!ft_strncmp(utils->envp[i], str, ft_strlen(str)))
			return (ft_substr(utils->envp[i], ft_strlen(str),
					ft_strlen(utils->envp[i]) - ft_strlen(str)));
		i++;
	}
	return (NULL);
}

int	specific_path(t_utils *utils, char *str)
{
	char	*tmp;
	int		ret;

	// using this function I compare the path passed by user with my environmental variable and save it in temp
	tmp = find_path_ret(str, utils);
	// and using chdir inbuilt function I change path will return 0 if it successfully changes the working directory
	ret = chdir(tmp);
	free(tmp);
	// if it didn't successfully change the directory it will go inside the if condition to print error
	if (ret != 0)
	{
		str = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_putstr_fd(str, STDERR_FILENO);
		free(str);
		ft_putendl_fd(" not set", STDERR_FILENO);
	}
	return (ret);
}
/*
The update_path_to_env function is responsible for 
updating the PWD and OLDPWD environment variables 
in the utils->envp array with the current and previous working directories, respectively.
*/
void	update_path_to_env(t_utils *utils)
{
	int		i;
	char	*tmp;

	i = 0;
	while (utils->envp[i])
	{
		// searching for PWD= in the envp double array and returns 0 when it finds it by comparing first 4 characters
		if (!ft_strncmp(utils->envp[i], "PWD=", 4))
		{
			// It will concatinate the new working directory with PWD= and update it in the env variable (PWD=/users/szerisen)
			tmp = ft_strjoin("PWD=", utils->pwd);
			free(utils->envp[i]);
			utils->envp[i] = tmp;
		}
		else if (!ft_strncmp(utils->envp[i], "OLDPWD=", 7) && utils->old_pwd)
		{
			// This will do the same thing as the first one which is concatinating OLDPWD= with the value of old_pwd
			tmp = ft_strjoin("OLDPWD=", utils->old_pwd);
			free(utils->envp[i]);
			utils->envp[i] = tmp;
		}
		i++;
	}
}

int	m_cd(t_utils *utils, t_cmds *cmds)
{
	int		ret;
	// if str[1] is empty the (i.e if the user passes cd without any option then this redirects him to home directory)
	if (!cmds->str[1])
		ret = specific_path(utils, "HOME=");
	// checking if the first argument (cmds->str[1]) starts with a hyphen ("-"). This means the user wants to go to previous directory.
	else if (ft_strncmp(cmds->str[1], "-", 1) == 0)
		ret = specific_path(utils, "OLDPWD=");
	else
	{
		ret = chdir(cmds->str[1]);
		// printing the string "minishell: " to the standard error file descriptor (incase there is an error while executing cd command)
		if (ret != 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			// this line is used to print the value of cmds->str[1] to the standard error stream. 
			ft_putstr_fd(cmds->str[1], STDERR_FILENO);
			perror(" ");
		}
	}
	// checks if the return value is not equal to 0. A return value of 0 typically indicates a successful execution of chdir.
	if (ret != 0)
		return (EXIT_FAILURE);
	// This function will update the pwd and old_pwd variables with the new paths. 
	change_path(utils);
	update_path_to_env(utils);
	return (EXIT_SUCCESS);
}
