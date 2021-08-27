/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:42:51 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/23 15:00:45 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "../include/libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*ptr;
	size_t	s_len;

	s_len = ft_strlen(s);
	ptr = malloc(s_len + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (*(s + i) != '\0')
	{
		*(ptr + i) = *(s + i);
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}
