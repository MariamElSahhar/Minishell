/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:43:10 by szerisen          #+#    #+#             */
/*   Updated: 2023/05/15 19:23:08 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	change_path(t_utils *utils)
{
	char	*tmp;

	tmp = ft_strdup(utils->pwd);
	free(utils->old_pwd);
	utils->old_pwd = tmp;
	free(utils->pwd);
	utils->pwd = getcwd(NULL, sizeof(NULL));
}