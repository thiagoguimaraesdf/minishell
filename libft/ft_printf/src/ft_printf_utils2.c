/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:16:31 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/23 14:57:57 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

void	ft_putlonglongint_fd(long long l, int fd)
{
	if (l > 0)
	{
		ft_putlonglongint_fd(l / 10, fd);
		ft_putchar_fd((l % 10) + '0', fd);
	}
	return ;
}

void	ft_putlongnbr_fd(long n, int fd)
{
	long long	l;

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
	ft_putlonglongint_fd(l, fd);
	return ;
}

t_flag	*new_t_flag(void)
{
	t_flag	*formats;

	formats = (t_flag *)malloc(sizeof(t_flag));
	if (formats == NULL)
		return (NULL);
	formats->flag = '\0';
	formats->width = 0;
	formats->precision = -1;
	return (formats);
}
