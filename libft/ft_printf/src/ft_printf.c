/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 16:07:29 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/23 14:58:02 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static size_t	type_router(va_list args, char type, t_flag *formats)
{
	if (type == 'i' || type == 'd')
		return (ft_handle_int(args, formats));
	else if (type == 's')
		return (ft_handle_str(args, formats));
	else if (type == 'c')
		return (ft_handle_char(args, formats));
	else if (type == 'x' || type == 'X')
		return (ft_handle_hexa(args, formats, type));
	else if (type == 'p')
		return (ft_handle_pointer(args, formats));
	else if (type == 'u')
		return (ft_handle_unsignedint(args, formats));
	else if (type == '%')
		return (ft_handle_percent(formats));
	else
		return (-1);
}

static int	syntax(va_list args, const char *str, t_flag *formats, int pos)
{
	int		syntax_cat;

	pos++;
	syntax_cat = check_syntax(str, pos);
	if (syntax_cat == -1)
		return (-1);
	while (!is_type(str[pos]))
	{
		syntax_cat = check_syntax(str, pos);
		if (syntax_cat == -1)
			return (-1);
		if (syntax_cat == 1)
			formats->precision = handle_precision(args, str, &pos);
		else if (syntax_cat == 3)
			formats->width = handle_width(args, str, &pos, formats);
		else if (syntax_cat == 2)
			formats->flag = handle_flag(str, &pos);
		pos++;
	}
	return (pos);
}

static int	print_placeholder(va_list args, const char *str, int *str_pos)
{
	t_flag		*formats;
	int			placeholder_size;

	placeholder_size = 0;
	formats = new_t_flag();
	if (formats == NULL)
		return (-1);
	*str_pos = syntax(args, str, formats, *str_pos);
	if (*str_pos == -1)
		return (-1);
	if (is_type(str[*str_pos]))
		placeholder_size = (int)type_router(args, str[*str_pos], formats);
	*str_pos = *str_pos + 1;
	free(formats);
	formats = NULL;
	return (placeholder_size);
}

static void	handle_normal_char(char c, int *str_pos, int *str_size)
{
	ft_putchar_fd(c, 1);
	*str_pos = *str_pos + 1;
	*str_size = *str_size + 1;
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		str_pos;
	int		str_size;
	int		placeholder_size;

	if (!str)
		return (ERROR);
	str_pos = 0;
	str_size = 0;
	placeholder_size = 0;
	va_start(args, str);
	while (str[str_pos] != '\0')
	{
		if (str[str_pos] != '%')
			handle_normal_char(str[str_pos], &str_pos, &str_size);
		else
		{
			placeholder_size = print_placeholder(args, str, &str_pos);
			if (placeholder_size == -1)
				return (-1);
			str_size = str_size + placeholder_size;
		}
	}
	va_end(args);
	return (str_size);
}
