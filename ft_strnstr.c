/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:34:42 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/06/06 04:55:14 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == 0)
		return ((char *) big);
	i = 0;
	while (i < len && *(big + i))
	{
		j = 0;
		while (i + j < len && *(little + j) && *(little + j) == *(big + i + j))
			j++;
		if (*(little + j) == 0)
			return ((char *) big + i);
		i++;
	}
	return ((char *) 0);
}
