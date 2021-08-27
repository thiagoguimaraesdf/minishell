/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 21:12:40 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/23 14:57:11 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../include/get_next_line.h"

int	init_read_buffer(int fd, char *read_b, int *read_p)
{
	int	read_size;

	read_size = 0;
	if (ft_strlen(read_b) == 0 || *read_p == BUFFER_SIZE)
		return (reset_read_buffer(fd, read_b, read_p));
	else
		return (ft_strlen(read_b + *read_p));
	return (read_size);
}

int	end_of_file(char **line, char **line_b, char *read_b, int read_size)
{
	if (read_size < 0)
		return (-1);
	*line_b = malloc(read_size + 1);
	if (*line_b == NULL)
		return (-1);
	ft_strlcpy(*line_b, read_b, read_size + 1);
	*line = *line_b;
	return (0);
}

char	*flb(char **line_b, int *read_p, char *read_b, int linebreak_p)
{
	*line_b = malloc(linebreak_p + 1);
	if (*line_b == NULL)
		return (NULL);
	ft_strlcpy(*line_b, (read_b + *read_p), linebreak_p + 1);
	*read_p = *read_p + linebreak_p + 1;
	return (*line_b);
}

char	*no_linebreak(int fd, char **line_b, char *read_b, int *read_p)
{
	char	*temp;
	int		linebreak_p;
	int		read_size;

	*line_b = malloc(ft_strlen(read_b + *read_p) + 1);
	ft_strlcpy(*line_b, read_b + *read_p, ft_strlen(read_b + *read_p) + 1);
	linebreak_p = -1;
	while (linebreak_p < 0)
	{
		temp = malloc(ft_strlen(*line_b) + 1);
		ft_strlcpy(temp, *line_b, ft_strlen(*line_b) + 1);
		read_size = reset_read_buffer(fd, read_b, read_p);
		if (read_size <= 0)
			break ;
		linebreak_p = find_newline(read_b, 0);
		if (linebreak_p >= 0)
		{
			*line_b = line_malloc_cpy(*line_b, temp, linebreak_p, read_b);
			*read_p = *read_p + linebreak_p + 1;
			return (*line_b);
		}
		*line_b = line_malloc_cpy(*line_b, temp, read_size, read_b);
	}
	free(temp);
	return (*line_b);
}

int	get_next_line(int fd, char **line)
{
	static char		read_b[BUFFER_SIZE + 1];
	static int		read_p = 0;
	static int		linebreak_p = 0;
	char			*line_b;
	int				read_size;

	read_size = init_read_buffer(fd, read_b, &read_p);
	if (read_size <= 0)
		return (end_of_file(line, &line_b, read_b, read_size));
	else
	{
		linebreak_p = find_newline(read_b + read_p, read_p);
		if (linebreak_p >= 0)
			*line = flb(&line_b, &read_p, read_b, linebreak_p);
		else
			*line = no_linebreak(fd, &line_b, read_b, &read_p);
		if (ft_strlen(read_b) == 0)
			return (0);
		return (1);
	}
}
