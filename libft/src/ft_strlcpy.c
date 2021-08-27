/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 09:25:01 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/23 15:00:54 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../include/libft.h"

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
