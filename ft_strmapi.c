/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 00:50:55 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/06/06 00:59:57 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret;
	size_t	len;
	size_t	i;

	if (!s)
		return ((char *) 0);
	len = ft_strlen(s);
	ret = (char *) malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (ret);
	i = 0;
	while (i < len)
	{
		*(ret + i) = f((unsigned int) i, *(s + i));
		i++;
	}
	return (ret);
}
