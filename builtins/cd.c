/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:42:47 by szerisen          #+#    #+#             */
/*   Updated: 2023/05/15 20:06:19 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *find_path_ret(char *str, t_utils *utils)
{
    int     i;

    i = 0;
    while (utils->envp[i])
    {
        if (!ft_strncmp(utils->envp[i], str, ft_strlen(str)))
            return (ft_substr(utils->envp[i], ft_strlen(str), ft_strlen(utils->envp) - ft_strlen(str)));
    }
    return (NULL);
}
int     specific_path(t_utils *utils, char *str)
{
    char    *tmp;
    int     retur;
    
    tmp = find_path_retur(str, utils);
    retur = chdir(tmp);
    free(tmp);
    if (retur != 0)
    {
        str = ft_substr(str, 0, ft_strlen(str) - 1);
        ft_putstr_fd(str, STDERR_FILENO);
        free(str);
        ft_putendl_fd(" not set", STDERR_FILENO);
    }
    return (retur);
}
void    update_path_to_env(t_utils *utils)
{
    int     i;
    char    *tmp;
    
    i = 0;
    while (utils->envp[i])
    {
        if (!ft_strncmp(utils->envp[i], "PWD=", 4))
        {
            tmp = ft_strjoin("PWD=", utils->pwd);
            free(utils->envp[i]);
            utils->envp[i] = tmp;
        }
        else if (!ft_strncmp(utils->envp[i], "OLDPWD=", 7) && utils->old_pwd)
        {
            tmp = ft_strjoin("OLDPWD=", utils->old_pwd);
            free(utils->envp[i]);
            utils->envp[i] = tmp;
        }
        i++;
    }
}

int cd(t_utils *utils, t_cmds *cmds)
{
    int     spit;
    
    if (!cmds->str[1])
        spit = specific_path(utils, "HOME=");
    else if (ft_strncmp(cmds->str[1], "-", 1) == 0)
        spit = specific_path(utils, "OLDPWD=");
    else
    {
        spit = chdir(cmds->str[1]);
        if (spit != 0)
        {
            ft_putstr_fd("minishell: ", STDERR_FILENO);
            ft_putstr_fd(cmds->str[1], STDERR_FILENO);
            perror(" ");
        }
    }    
    if (spit != 0)
        return (EXIT_FAILURE);
    change_path(utils);
    update_path_to_env(utils);
    return (EXIT_SUCCESS);
}
// void	free_arr(char **split_arr)
// {
// 	int	i;

// 	i = 0;
// 	while (split_arr[i])
// 	{
// 		free(split_arr[i]);
// 		i++;
// 	}
// 	free(split_arr);
// }

// char	**ft_arrdup(char **arr)
// {
// 	char	**rtn;
// 	size_t	i;

// 	i = 0;
// 	while (arr[i] != NULL)
// 		i++;
// 	rtn = ft_calloc(sizeof(char *), i + 1);
// 	if (!rtn)
// 		return (NULL);
// 	i = 0;
// 	while (arr[i] != NULL)
// 	{
// 		rtn[i] = ft_strdup(arr[i]);
// 		if (rtn[i] == NULL)
// 		{
// 			free_arr(rtn);
// 			return (rtn);
// 		}
// 		i++;
// 	}
// 	return (rtn);
// }
// int main(int ac, char **av, char **envp )
// {
//     t_utils utils;
//     t_cmds  cmds;

//     utils.envp = ft_arrdup(envp);
//     // initialize the utils structure with appropriate values
//     utils.pwd = "/Users/szerisen/Desktop/minishell";
//     utils.old_pwd = "/Users/szerisen/Desktop/";
 
//     // initialize the cmds structure with appropriate values
//     cmds.str[0] = "cd";
//     cmds.str[1] = "/Users/szerisen/";

//     // call the cd function
//     cd(&utils, &cmds);

//     return (0);
// }

 