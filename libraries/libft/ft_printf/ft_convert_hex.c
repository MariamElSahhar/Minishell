/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:17:31 by szeris            #+#    #+#             */
/*   Updated: 2023/05/11 21:04:42 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_print_hex(unsigned long n, char *up_or_low)
{
	if (n != 0)
	{
		ft_print_hex(n / 16, up_or_low);
		ft_putchar_fd(up_or_low[n % 16], 1);
	}
}

int	ft_convert_hex(unsigned long n, char *up_or_low)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		ft_putchar_fd(up_or_low[n], 1);
		return (1);
	}
	ft_print_hex(n, up_or_low);
	while (n != 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}
