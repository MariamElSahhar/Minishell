/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_if_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:17:46 by szeris            #+#    #+#             */
/*   Updated: 2023/05/11 21:04:42 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_if_char(char c, va_list ap)
{
	if (c == 'c')
	{
		ft_putchar_fd(va_arg(ap, int), 1);
		return (1);
	}
	if (c == 's')
		return (ft_putstr_size(va_arg(ap, char *), 1));
	return (0);
}
