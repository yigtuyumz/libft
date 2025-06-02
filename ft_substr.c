/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:55:17 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/06/02 22:04:20 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;

	ret = (char *) malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (ret);

	i = 0;
	while (i < len && *(s + start + i))
	{
		*(ret + i) = *(s + start + i);
		i++;
	}
	*(ret + i) = 0;
	return (ret);
}
