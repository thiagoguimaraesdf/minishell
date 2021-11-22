/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 21:50:05 by tguimara          #+#    #+#             */
/*   Updated: 2021/11/15 23:15:20 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_command(t_pipeline	*pipeline)
{
	if (!ft_strncmp(pipeline->command_list->command, "exit", 4))
		g_shell_config->should_continue = false;
}

int	end_var_pos(char *str)
{
	int	i;

	i = 1;
	while (str && str[i])
	{
		if (str[i] == '\"' | str[i] == '\'' | str[i] == '$' | str[i] == ' ')
		{
			return (i - 1);
		}
		i++;
	}
	return (i - 1);
}
