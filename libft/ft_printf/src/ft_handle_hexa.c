/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:34:26 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/23 14:57:40 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static char	*convert_hexa(unsigned long long u, char *base)
{
	unsigned int		base_len;
	unsigned int		hexa_size;
	char				*hexa_str;

	base_len = ft_strlen(base);
	hexa_size = count_digits(u, base_len);
	hexa_str = (char *)malloc(hexa_size + 1);
	hexa_str[hexa_size] = '\0';
	while (u > 0)
	{
		if (u < base_len)
		{
			hexa_str[hexa_size - 1] = base[u];
			break ;
		}
		else
		{
			hexa_str[hexa_size - 1] = base[u % base_len];
			hexa_size--;
			u = u / base_len;
		}
	}
	return (hexa_str);
}

static char 	*ft_toupper_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] >= 'a' && str[i] <= 'z'))
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}

static void	ft_print_hexa(char *hexa_str, char type)
{
	if (type == 'X')
		ft_putstr_fd(ft_toupper_str(hexa_str), 1);
	else
		ft_putstr_fd(hexa_str, 1);
}

static size_t	ft_print_uint(char *str, t_flag *formats, char t, int size)
{
	int		hexa_digits;
	size_t	align_size;

	align_size = 0;
	hexa_digits = ft_strlen(str);
	if (formats->flag == '-')
	{
		print_align(size, '0', hexa_digits);
		ft_print_hexa(str, t);
		align_size = print_align(formats->width, '\0', size);
	}
	else if (formats->flag == '0')
	{
		print_align(size, '0', hexa_digits);
		align_size = print_align(formats->width, '0', size);
		ft_print_hexa(str, t);
	}
	else
	{
		align_size = print_align(formats->width, '\0', size);
		print_align(size, '0', hexa_digits);
		ft_print_hexa(str, t);
	}
	free(str);
	return (size + align_size);
}		

size_t	ft_handle_hexa(va_list args, t_flag *formats, char type)
{
	unsigned int	u;
	char			*hexa_str;
	int				hexa_size;

	u = va_arg(args, unsigned int);
	if (u == 0 && formats->precision == 0)
	{
		print_align(formats->width, '\0', 0);
		return (formats->width);
	}
	if (u == 0)
		hexa_str = ft_strdup("0");
	else
		hexa_str = convert_hexa(u, "0123456789abcdef");
	hexa_size = ft_strlen(hexa_str);
	if (formats->precision >= 0 && formats->flag == '0')
		formats->flag = '\0';
	if (formats->precision > 0 && formats->precision >= hexa_size)
		hexa_size = formats->precision;
	return (ft_print_uint(hexa_str, formats, type, hexa_size));
}
