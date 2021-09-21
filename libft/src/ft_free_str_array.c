/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:43:08 by tguimara          #+#    #+#             */
/*   Updated: 2021/09/21 15:48:54 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void 	ft_free_str_array(char ***str_array)
{
	if (!(**str_array))
		return ;
	while (*str_array)
	{
		free(*str_array);
		*str_array = NULL;
		**str_array = **str_array + 1;
	}
	free(**str_array);
	**str_array = NULL;
}
