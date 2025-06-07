/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 00:50:55 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/06/08 01:11:22 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ret;
	size_t			len;
	unsigned int	i;

	if (!s || !f)
		return ((char *) 0);
	len = ft_strlen(s);
	ret = (char *) malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (ret);
	i = 0;
	while (i < len)
	{
		*(ret + i) = f(i, *(s + i));
		i++;
	}
	*(ret + i) = 0;
	return (ret);
}
