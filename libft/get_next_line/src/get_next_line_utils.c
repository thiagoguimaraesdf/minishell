/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:07:32 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/23 14:57:18 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../include/get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*(s + len) != '\0')
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*src_cpy;

	if (dst == NULL || src == NULL)
		return (0);
	src_cpy = (const char *)src;
	if (size == 0)
		return (ft_strlen(src));
	while (size > 1 && *src_cpy != '\0')
	{
		*dst = *src_cpy;
		dst++;
		src_cpy++;
		size--;
	}
	if (size > 0)
		*dst = '\0';
	return (ft_strlen(src));
}

int	find_newline(const char *s, int start)
{
	int		i;

	i = 0;
	while (i < BUFFER_SIZE - start)
	{
		if (*(s + i) == 10)
			return (i);
		i++;
	}
	return (-1);
}

int	reset_read_buffer(int fd, char *read_b, int *read_p)
{
	int	read_size;
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		read_b[i] = '\0';
		i++;
	}
	read_size = read(fd, read_b, BUFFER_SIZE);
	read_b[read_size] = '\0';
	*read_p = 0;
	return (read_size);
}

char	*line_malloc_cpy(char *line_b, char *temp, int read_size, char *read_b)
{
	free(line_b);
	line_b = malloc(ft_strlen(temp) + read_size + 1);
	ft_strlcpy(line_b, temp, ft_strlen(temp) + 1);
	ft_strlcpy(line_b + ft_strlen(temp), read_b, read_size + 1);
	free(temp);
	temp = NULL;
	return (line_b);
}
