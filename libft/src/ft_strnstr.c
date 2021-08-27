/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 09:48:03 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/23 15:01:06 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../include/libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	s2_len;

	s2_len = ft_strlen(s2);
	i = 0;
	if (s2_len == 0)
		return ((char *)s1);
	else if (s2_len > ft_strlen(s1) || len == 0)
		return (NULL);
	while (i <= len - s2_len && *(s1 + i))
	{
		if (*(s1 + i) == *(s2))
		{
			j = 0;
			while (*(s2 + j) != '\0' && (*(s1 + i + j) == *(s2 + j)))
				j++;
			if (j == s2_len)
				return ((char *)(s1 + i));
		}
		i++;
	}
	return (NULL);
}
