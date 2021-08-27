/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:31:31 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/23 15:01:03 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../include/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && *s1 && *s2)
	{
		if ((unsigned char)(*s1) == (unsigned char)(*s2))
		{
			i++;
			s1++;
			s2++;
		}
		else
			return ((unsigned char)(*s1) - (unsigned char)(*s2));
	}
	if ((unsigned char)(*s1) != (unsigned char)(*s2) && i < n)
		return ((unsigned char)(*s1) - (unsigned char)(*s2));
	return (0);
}
