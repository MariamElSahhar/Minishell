/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:18:44 by szeris            #+#    #+#             */
/*   Updated: 2023/05/11 21:04:42 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	ret;
	int	p_n;
	int	i;

	i = 0;
	ret = 0;
	p_n = 1;
	while (*str == ' ' || (*str > 8 && *str < 14))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			p_n *= -1;
		str++;
	}
	while (ft_isdigit(str[i]) == 1)
	{
		ret = (ret * 10) + (str[i] - '0');
		i++;
		if (i == 10 && str[i] && p_n == -1)
			return (0);
		else if (i == 10 && str[i])
			return (-1);
	}
	return (ret * p_n);
}
