/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:25:12 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/23 14:57:49 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static void	ft_putnstr_fd(char *s, int fd, size_t s_size)
{
	size_t	i;

	if (s == NULL)
		return ;
	i = 0;
	while (*(s + i) != '\0' && i < s_size)
	{
		write(fd, (s + i), 1);
		i++;
	}
}

static size_t	ft_print_str(char *s, int print_size, int width, char flag)
{
	size_t	align_size;

	align_size = 0;
	if (flag == '-')
	{
		ft_putnstr_fd(s, 1, print_size);
		align_size = print_align(width, '\0', print_size);
		return (print_size + align_size);
	}
	align_size = print_align(width, '\0', print_size);
	ft_putnstr_fd(s, 1, print_size);
	return (print_size + align_size);
}

size_t	ft_handle_str(va_list args, t_flag *formats)
{
	char	*s;
	size_t	print_size;
	int		width;
	char	flag;

	width = formats->width;
	flag = formats->flag;
	s = va_arg(args, char *);
	if (!s)
		s = "(null)";
	print_size = ft_strlen(s);
	if (formats->precision >= 0 && formats->precision < (int)print_size)
		print_size = (size_t)formats->precision;
	return (ft_print_str(s, print_size, width, flag));
}
