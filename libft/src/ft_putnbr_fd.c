/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:22:57 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/23 15:00:37 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../include/libft.h"

static void	ft_putunsgint_fd(unsigned int l, int fd)
{
	if (l > 0)
	{
		ft_putunsgint_fd(l / 10, fd);
		ft_putchar_fd((l % 10) + '0', fd);
	}
	return ;
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	l;

	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		l = n * (-1);
	}
	else
		l = n;
	ft_putunsgint_fd(l, fd);
	return ;
}
