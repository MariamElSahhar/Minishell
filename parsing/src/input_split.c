/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:58:39 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/16 19:02:50 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	**join_str(char **arr, char *str);
void	skip_quotes(char *input, int *i);
char	**split_input(char *input);
