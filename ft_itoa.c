/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:52:19 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/06/08 01:51:55 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	get_malloc_sz(int nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (2);
	if (nb < 0)
		count++;
	while (nb != 0)
	{
		nb /= 10;
		count++;
	}
	return (++count);
}

char	*ft_itoa(int n)
{
	char	*buffer;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = get_malloc_sz(n);
	buffer = (char *) malloc(sizeof(char) * len);
	if (!buffer)
		return ((char *) 0);
	if (n < 0)
	{
		*(buffer + 0) = '-';
		n = -n;
	}
	*(buffer + --len) = 0;
	while (n != 0)
	{
		*(buffer + --len) = '0' + (n % 10);
		n /= 10;
	}
	return (buffer);
}
