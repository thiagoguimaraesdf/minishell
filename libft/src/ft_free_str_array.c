/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:43:08 by tguimara          #+#    #+#             */
/*   Updated: 2021/10/07 05:39:34 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/libft.h"

#include <stdio.h>

void	ft_free_str_array(char **str_array)
{
	if (!(str_array))
		return ;
	while (str_array && *str_array)
	{
		free(*str_array);
		*str_array = NULL;
		str_array++;
	}
}
