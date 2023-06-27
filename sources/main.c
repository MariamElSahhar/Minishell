/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:44:48 by szerisen          #+#    #+#             */
/*   Updated: 2023/06/24 19:07:46 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_arr(char **split_arr)
{
	int	i;

	i = 0;
	while (split_arr[i])
	{
		free(split_arr[i]);
		i++;
	}
	free(split_arr);
}

int	main(int argc, char **argv, char **envp)
{
	t_utils	utils;

	if (argc != 1 || argv[1])
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
	init_signals();
	utils.envp = ft_arrdup(envp);
	find_pwd(&utils);
	implement_utils(&utils);
	printf("\n%s\n\n", WELCOME_MSG);
	minishell_loop(&utils);
	return (0);
}
