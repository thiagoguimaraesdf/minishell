/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:09:20 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/23 15:04:57 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		find_newline(const char *s, int start);
int		reset_read_buffer(int fd, char *read_b, int *read_p);
int		init_read_buffer(int fd, char *read_b, int *read_p);
int		end_of_file(char **line, char **line_b, char *read_b, int read_size);
char	*line_malloc_cpy(char *line_b, char *temp, int read_size, char *read_b);
char	*no_linebreak(int fd, char **line_b, char *read_b, int *read_p);
char	*flb(char **line_b, int *read_p, char *read_b, int linebreak_p);
int		get_next_line(int fd, char **line);

#endif
