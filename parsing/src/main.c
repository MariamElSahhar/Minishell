/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:09:53 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/09 18:55:22 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	parse_input(char *input)
{
	char	**sep;
	// int		i;

	sep = ft_split(input, ' ');
}

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		add_history((const char *) input);
		parse_input(input);
		free(input);
	}
	return (0);
}
