/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 01:54:56 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/05/27 21:47:58 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return (c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v' || c == ' ');
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	int		nb;

	nb = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(*(str + i)))
		i++;
	if (*(str + i) == '-')
	{
		sign = -1;
		i++;
	}
	else if (*(str + i) == '+')
		i++;
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		nb = (nb * 10) + (*(str + i) - '0');
		i++;
	}
	return (nb * sign);
}
