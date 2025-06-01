/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:55:17 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/06/01 16:45:52 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*ret;

	ret = (char *) malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (ret);

	while (*(s + start) && len--)
		*(ret + len) = *(s + start);

	return (ret);
}

