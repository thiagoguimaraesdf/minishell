/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 09:47:07 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/27 09:37:27 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

int	main(void)
{
	int			exit;
	char		**tokens;
	static char	*buffer;
	t_command	**commands;
	
	exit = 0;
	handle_signals();
	while (!exit)
	{
		buffer = readline("ft_shell>");
		if (buffer && *buffer)
			add_history(buffer);
		commands = commandList(buffer);
		while (commands)
		{
			commands++;
		}
		free(buffer);
		buffer = (char *)NULL;
	}
	return (0);
}
