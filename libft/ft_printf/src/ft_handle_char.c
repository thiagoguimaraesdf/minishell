/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:33:23 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/23 14:57:32 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static size_t	ft_print_char(char c, int width, char flag)
{
	size_t	align_size;

	align_size = 0;
	if (flag == '-')
	{
		write(1, &c, 1);
		align_size = print_align(width, '\0', 1);
		return (1 + align_size);
	}
	align_size = print_align(width, '\0', 1);
	write(1, &c, 1);
	return (1 + align_size);
}

size_t	ft_handle_char(va_list args, t_flag *formats)
{
	char	c;
	int		width;
	char	flag;

	width = formats->width;
	flag = formats->flag;
	c = va_arg(args, int);
	return (ft_print_char(c, width, flag));
}
