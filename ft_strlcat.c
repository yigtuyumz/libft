/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:39:03 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/06/08 01:33:36 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;
	size_t	len2;

	len = ft_strlen(dst);
	len2 = ft_strlen(src);
	i = 0;
	if (size <= len)
		return (size + len2);
	while (i < len2 && (len + i < size - 1))
	{
		*(dst + len + i) = *(src + i);
		i++;
	}
	*(dst + len + i) = 0;
	return (len + len2);
}
