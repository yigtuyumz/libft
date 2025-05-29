/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 00:32:33 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/05/28 20:43:01 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*d;
	char			*ret;

	ret = 0;
	d = (unsigned char *) s;
	while (*d)
	{
		if (*d == (unsigned char) c)
			ret = (char *) d;
		d++;
	}
	if (c == 0)
		return ((char *) d);
	return (ret);
}
