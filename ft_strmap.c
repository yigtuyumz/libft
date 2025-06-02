/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 21:20:24 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/06/02 21:58:54 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
{
	size_t	len;
	size_t	i;
	char	*ret;

	if (!s)
		return ((char *) 0);
	len = ft_strlen(s);
	ret = (char *) malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (ret);
	i = 0;
	while (i < len)
	{
		*(ret + i) = f(*(s + i));
		i++;
	}
	*(ret + i) = 0;
	return (ret);
}
