/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:48:23 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/05/31 14:27:37 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	char	cc;

	cc = (char) c;
	return ((cc >= 'a' && cc <= 'z') || (cc >= 'A' && cc <= 'Z'));
}
