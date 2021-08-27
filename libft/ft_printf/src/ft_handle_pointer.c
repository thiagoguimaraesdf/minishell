/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:37:31 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/23 14:57:47 by tguimara         ###   ########.fr       */
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

size_t	ft_handle_pointer(va_list args, t_flag *formats)
{
	unsigned long long	ptr_address;
	char				*hexa_ptr;
	size_t				hexa_size;
	size_t				align_size;

	ptr_address = va_arg(args, unsigned long long);
	if (ptr_address == 0)
		hexa_ptr = ft_strdup("0");
	else
		hexa_ptr = convert_hexa(ptr_address, "0123456789abcdef");
	hexa_size = ft_strlen(hexa_ptr) + 2;
	if (formats->flag != '-')
		align_size = print_align(formats->width, '\0', (int)hexa_size);
	ft_putstr_fd("0x", 1);
	ft_putstr_fd(hexa_ptr, 1);
	if (formats->flag == '-')
		align_size = print_align(formats->width, '\0', (int)hexa_size);
	free(hexa_ptr);
	hexa_ptr = NULL;
	return (hexa_size + align_size);
}
