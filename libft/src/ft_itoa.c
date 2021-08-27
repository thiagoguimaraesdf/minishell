/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 09:00:09 by tguimara          #+#    #+#             */
/*   Updated: 2021/06/06 16:24:31 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static	int	ft_countint(long n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n = -1 * n;
		i++;
	}
	while (n / 10 >= 1)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static	char	*ft_putnbr(char *ptr, long n, int size)
{
	int	start;

	start = 0;
	*(ptr + size) = '\0';
	if (n < 0)
	{
		start = 1;
		*(ptr) = '-';
		n = -1 * n;
	}
	while (size - 1 >= start)
	{
		*(ptr + size - 1) = ((n % 10) + '0');
		n = n / 10;
		size--;
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		size;
	long	nb;

	nb = n;
	size = ft_countint(nb);
	ptr = (char *)malloc(sizeof(char) * size + 1);
	if (ptr == NULL)
		return (NULL);
	ptr = ft_putnbr(ptr, nb, size);
	return (ptr);
}
