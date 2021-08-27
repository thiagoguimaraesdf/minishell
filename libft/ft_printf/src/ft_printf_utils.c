/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:16:31 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/23 14:57:55 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	is_type(char c)
{
	if (c == '%' || c == 'd' || c == 'i' || c == 'u' || c == 'x'
		|| c == 'X' || c == 's' || c == 'c' || c == 'p')
		return (1);
	return (0);
}

int	is_flag(char c)
{
	if (c == '0' || c == '-')
		return (1);
	return (0);
}

int	check_syntax(const char *str, int str_pos)
{
	if (str[str_pos] == '.')
		return (1);
	else if (is_flag(str[str_pos]) && str[str_pos - 1] == '%')
		return (2);
	else if (ft_isdigit(str[str_pos]) || str[str_pos] == '*')
		return (3);
	else if (is_type(str[str_pos]))
		return (4);
	else
		return (-1);
}

size_t	print_align(int width, char flag, int size)
{
	size_t	align_size;

	align_size = 0;
	if (width > 0 && width > size)
	{
		while (width > size)
		{
			if (flag == '\0')
				write(1, " ", 1);
			else if (flag == '0')
				write(1, "0", 1);
			width--;
			align_size++;
		}
	}
	return (align_size);
}

int	count_digits(unsigned long long u, unsigned int base_len)
{
	int					i;
	unsigned long long	value;

	i = 0;
	value = u;
	if (value == 0)
		return (1);
	while (value >= 1)
	{
		value = value / base_len;
		i++;
	}
	return (i);
}
