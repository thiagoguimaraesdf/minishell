/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 08:53:45 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/23 15:01:13 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "../include/libft.h"

static char	*ft_secure_malloc(char *ptr, size_t start,
		unsigned int s_len, size_t len)
{
	if (start >= s_len)
		ptr = malloc(sizeof(char) * 1);
	else if (len > s_len - start)
		ptr = malloc(sizeof(char) * (s_len - start + 1));
	else
		ptr = malloc(sizeof(char) * (len + 1));
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	j;
	unsigned int	s_len;
	char			*ptr;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	ptr = NULL;
	ptr = ft_secure_malloc(ptr, start, s_len, len);
	if (ptr == NULL)
		return (NULL);
	j = 0;
	if (start < s_len)
	{
		while (len > 0 && s[start] != '\0')
		{
			ptr[j] = s[start];
			j++;
			start++;
			len--;
		}
	}
	ptr[j] = '\0';
	return (ptr);
}
