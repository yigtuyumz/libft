/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:30:03 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/05/31 13:44:12 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ft_puthexa_fd(int fd, unsigned long int nb, unsigned char addrlen)
{
	unsigned char	temp;
	unsigned char	iterator;

	iterator = 0x00;
	while (iterator++ < addrlen)
	{
		temp = ((nb >> ((addrlen * 0x08) - (iterator * 0x08))) & 0xF0) >> 0x04;
		if (temp >= 0x0A)
			temp = 0x61 + (temp % 0x0A);
		else
			temp += 0x30;
		write(fd, &temp, 1);
		temp = (nb >> ((addrlen * 8) - (iterator * 8))) & 0x0F;
		if (temp >= 0x0A)
			temp = 0x61 + (temp % 0x0A);
		else
			temp += 0x30;
		write(fd, &temp, 0x01);
	}
	if (addrlen == 8)
		write(fd, ":", 0x01);
}

static void	ft_putascii_fd(int fd, char c)
{
	if (c >= 32 && c <= 126)
		write(fd, &c, 0x01);
	else
		write(fd, ".", 0x01);
}

static void	ft_hexaloop_fd(int fd, void *addr, unsigned int *iter, unsigned int size)
{
	unsigned int	iternext;

	iternext = *iter + 0x10;
	while (*iter < iternext)
	{
		if (*iter % 0x02 == 0x00)
			write(fd, " ", 1);
		if (*iter < size)
			ft_puthexa_fd(fd, ((char *) addr)[*iter], 0x01);
		else
			write(fd, "  ", 0x02);
		*iter += 1;
	}
}

void	*ft_print_memory_fd(int fd, void *addr, unsigned int size)
{
	unsigned int	iter;
	unsigned int	iternext;

	if (!addr)
		return ((void *) 0);
	iter = 0x00;
	while (iter < size)
	{
		iternext = iter + 0x10;
		if (iter % 0x10 == 0x00)
		{
			ft_puthexa_fd(fd, (unsigned long int) &((char *) addr)[iter], 0x08);
			ft_hexaloop_fd(fd, addr, &iter, size);
			write(fd, " ", 0x01);
			iter -= 0x10;
			while ((iter < iternext) && (iter < size))
				ft_putascii_fd(fd, ((char *) addr)[iter++]);
			write(fd, "\n", 0x01);
		}
	}
	return (addr);
}
