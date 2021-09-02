/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandChecker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 09:34:41 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/27 10:16:46 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

/*
	CommandChecker must verify if:
	
		1. First string is one of the two cases:
			- Minishell buil-in
			- Executable avaiable in PATH
		2. If there is a redirection, check if following string is a filename
		
*/

int	commandChecker(t_command *command, char **builtinList)
{
	char	**path;
	char 	*cur_path;
	int		i;
	
	path = ft_split(PATH, ':');
	cur_path = (char *)malloc(sizeof(char) * 100);
	cur_path = getcwd(cur_path, 100);
	// command checker
	// cur dir
	
	while (path[i])
	{

		
	}
	// filename checker
	
}