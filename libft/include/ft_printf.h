/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 10:43:02 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/23 15:04:11 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define ERROR 1
# include "libft.h"
# include <stdarg.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_flag {
	int		width;
	int		precision;
	char	flag;
}	t_flag;

int		ft_printf(const char *str, ...);
int		is_type(char c);
int		is_flag(char c);
int		check_syntax(const char *str, int str_pos);
size_t	print_align(int width, char flag, int size);
int		count_digits(unsigned long long u, unsigned int base_len);
void	ft_putlonglongint_fd(long long l, int fd);
void	ft_putlongnbr_fd(long n, int fd);
size_t	ft_handle_int(va_list args, t_flag *formats);
size_t	ft_handle_str(va_list args, t_flag *formats);
size_t	ft_handle_char(va_list args, t_flag *formats);
size_t	ft_handle_hexa(va_list args, t_flag *formats, char type);
size_t	ft_handle_pointer(va_list args, t_flag *formats);
size_t	ft_handle_unsignedint(va_list args, t_flag *formats);
size_t	ft_handle_percent(t_flag *formats);
int		handle_precision(va_list args, const char *str, int *str_pos);
int		handle_width(va_list args, const char *str, int *pos, t_flag *formats);
char	handle_flag(const char *str, int *str_pos);
t_flag	*new_t_flag(void);

#endif
