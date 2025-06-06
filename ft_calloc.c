/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 00:08:38 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/06/06 00:49:39 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;

	if (!nmemb || !size || (nmemb > (((size_t) -1) / size)))
		return (malloc(1));
	nmemb *= size;
	ret = malloc(nmemb);
	if (!ret)
		return (ret);
	ft_bzero(ret, nmemb);
	return (ret);
}
