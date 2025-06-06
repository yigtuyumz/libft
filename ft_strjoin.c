/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 01:48:59 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/06/06 02:24:08 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*ret;

	ret = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
		return ((char *) 0);
	i = 0;
	while (*s1)
		*(ret + i++) = *(s1++);
	while (*s2)
		*(ret + i++) = *(s2++);
	*(ret + i) = 0;
	return (ret);
}