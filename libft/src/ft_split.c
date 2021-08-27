/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 17:50:52 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/23 15:00:42 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "../include/libft.h"

static int	ft_countwords(char *p, char c)
{
	int		words;
	int		i;

	words = 0;
	i = 0;
	while (*(p + i) == c && *(p + i) != '\0')
		i++;
	if (*(p + i) == '\0')
		return (words);
	while (*(p + i) != '\0')
	{
		if (i == 0 && *(p + i) != c)
			words++;
		if (i > 0 && *(p + i) != c && *(p + i - 1) == c)
			words++;
		i++;
	}
	if (words == 0)
		return (1);
	return (words);
}

static int	ft_size(char const *s, char c)
{
	int	size;
	int	w;

	size = 0;
	w = 0;
	while (*(s + w) != '\0' && *(s + w) == c)
		w++;
	while (*(s + size + w) != '\0' && *(s + size + w) != c)
		size++;
	return (size);
}

static char	*ft_fillstr(char *tab, char *ptr, char c)
{
	int	k;

	k = 0;
	while (*(ptr) == c && *(ptr) != '\0')
		ptr++;
	while (*(ptr) != c && *(ptr) != '\0')
	{
		*(tab + k) = *ptr;
		ptr++;
		k++;
	}
	*(tab + k) = '\0';
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	int		wordcount;
	int		i;
	char	**tab;
	char	*ptr;

	if (s == NULL)
		return (NULL);
	ptr = (char *)s;
	wordcount = ft_countwords(ptr, c);
	tab = (char **)malloc(sizeof(char *) * (wordcount + 1));
	if (tab)
	{
		i = 0;
		while (i < wordcount && tab)
		{
			tab[i] = malloc(sizeof(char) * (ft_size((ptr), c) + 1));
			if (!tab[i])
				return (NULL);
			ptr = ft_fillstr(tab[i], ptr, c);
			i++;
		}
		tab[i] = NULL;
		return (tab);
	}
	return (NULL);
}
