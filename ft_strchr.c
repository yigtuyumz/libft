/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:40:10 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/05/28 23:15:16 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	const unsigned char *d;

	d = (const unsigned char *) s;

	while (*d && *d != (unsigned char) c)
		d++;
	if (*d == (unsigned char) c || (unsigned char) c == 0)
		return ((char *) d);
	return (0);
}
