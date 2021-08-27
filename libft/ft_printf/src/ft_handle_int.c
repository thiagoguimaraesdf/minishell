/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:26:05 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/23 14:57:42 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static void	ft_print_neg_align(int neg, int i_size, int i_digits)
{
	if (neg == 1)
		ft_putchar_fd('-', 1);
	print_align(i_size, '0', i_digits);
}

static size_t	ft_print_int(long u, t_flag *formats, int i_size, int neg)
{
	int		i_digits;
	size_t	align_size;

	i_digits = count_digits(u, 10);
	align_size = 0;
	if (formats->flag == '-')
	{
		ft_print_neg_align(neg, i_size, i_digits);
		ft_putlongnbr_fd(u, 1);
		align_size = print_align(formats->width - neg, '\0', i_size);
	}
	else if (formats->flag == '0')
	{
		ft_print_neg_align(neg, i_size, i_digits);
		align_size = print_align(formats->width - neg, '0', i_size);
		ft_putlongnbr_fd(u, 1);
	}
	else
	{
		align_size = print_align(formats->width - neg, '\0', i_size);
		ft_print_neg_align(neg, i_size, i_digits);
		ft_putlongnbr_fd(u, 1);
	}
	return (i_size + align_size + neg);
}

size_t	ft_handle_int(va_list args, t_flag *formats)
{
	int		i_size;
	int		neg;
	long	u;

	u = va_arg(args, int);
	if (u == 0 && formats->precision == 0)
	{
		print_align(formats->width, '\0', 0);
		return (formats->width);
	}
	neg = 0;
	if (u < 0)
	{
		u = u * (-1);
		neg = 1;
	}
	i_size = count_digits(u, 10);
	if (formats->precision >= 0 && formats->flag == '0')
		formats->flag = '\0';
	if (formats->precision > 0 && formats->precision >= i_size)
		i_size = formats->precision;
	return (ft_print_int(u, formats, i_size, neg));
}
