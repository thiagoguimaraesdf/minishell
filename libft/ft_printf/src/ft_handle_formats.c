/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_formats.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:46:49 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/23 14:57:38 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	handle_precision(va_list args, const char *str, int *str_pos)
{
	int	precision;

	if (str[*str_pos + 1] == '*')
		precision = va_arg(args, int);
	else if (ft_isdigit(str[*str_pos + 1]))
		precision = ft_atoi((str + *str_pos + 1));
	else if (is_type(str[*str_pos + 1]))
		precision = 0;
	else
		return (ERROR);
	while (!is_type(str[*str_pos + 1]))
		*str_pos = *str_pos + 1;
	return (precision);
}

int	handle_width(va_list args, const char *str, int *pos, t_flag *formats)
{
	int	width;

	if (str[*pos] == '*')
	{
		width = va_arg(args, int);
		if (width < 0)
		{
			formats->flag = '-';
			width = width * (-1);
		}
	}
	else if (ft_isdigit(str[*pos]))
		width = ft_atoi((str + *pos));
	else
		return (ERROR);
	while (!is_type(str[*pos + 1]) && str[*pos + 1] != '.')
		*pos = *pos + 1;
	return (width);
}

char	handle_flag(const char *str, int *pos)
{
	char	flag;

	flag = '\0';
	while (is_flag(str[*pos]) && str[*pos])
	{
		if (flag != '-')
			flag = str[*pos];
		*pos = *pos + 1;
	}
	*pos = *pos - 1;
	return (flag);
}
