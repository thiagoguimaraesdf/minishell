/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_unsignedint.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:39:06 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/23 14:57:52 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static size_t	ft_print_uint(unsigned int u, int width, char flag, int u_size)
{
	unsigned int	u_digits;
	size_t			align_size;

	u_digits = count_digits(u, 10);
	align_size = 0;
	if (flag == '-')
	{
		print_align(u_size, '0', u_digits);
		ft_putlongnbr_fd(u, 1);
		align_size = align_size + print_align(width, '\0', u_size);
	}
	else if (flag == '0')
	{
		print_align(u_size, '0', u_digits);
		align_size = print_align(width, '0', u_size);
		ft_putlongnbr_fd(u, 1);
	}
	else
	{
		align_size = print_align(width, '\0', u_size);
		print_align(u_size, '0', u_digits);
		ft_putlongnbr_fd(u, 1);
	}
	return (u_size + align_size);
}

size_t	ft_handle_unsignedint(va_list args, t_flag *formats)
{
	unsigned int	u;
	size_t			u_size;
	int				width;
	char			flag;

	width = formats->width;
	flag = formats->flag;
	u = va_arg(args, unsigned int);
	if (u == 0 && formats->precision == 0)
	{
		print_align(width, '\0', 0);
		return (width);
	}
	u_size = count_digits(u, 10);
	if (formats->precision >= 0 && flag == '0')
		flag = '\0';
	if (formats->precision > 0 && formats->precision >= (int)u_size)
		u_size = (size_t)formats->precision;
	return (ft_print_uint(u, width, flag, u_size));
}
