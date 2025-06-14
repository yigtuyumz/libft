/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 00:08:38 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/06/07 21:42:51 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;

	if (!nmemb || !size)
	{
		ret = malloc(1);
		if (!ret)
			return ((void *) 0);
		return (ret);
	}
	if (nmemb > (size_t)(((size_t) 0xFFFFFFFFFFFFFFFF) / size))
		return ((void *) 0);
	nmemb *= size;
	ret = malloc(nmemb);
	if (!ret)
		return ((void *) 0);
	ft_bzero(ret, nmemb);
	return (ret);
}
