/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 09:47:07 by tguimara          #+#    #+#             */
/*   Updated: 2021/09/03 11:07:21 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

int 	add_builtin(char **builtinList, char *builtin)
{
	int i;

	i = 0;
	/*
		IMPLEMENT BUILTIN INSERTION
	*/
	return (i);
}

static char	**findPath(char **env)
{
	char **path;
	
	path = NULL;
	while (*env)
	{
		if (!ft_strncmp(*env, "PATH", 4))
		{
			printf("env:%s\n", *env);
			path = ft_split(*env,':');
		}
		env++;
	}
	*path = ft_strtrim(*path, "PATH=");
	return (path);	
}

int	main(int argc, char **argv, char **env)
{
	int			exit;
	char		**tokens;
	static char	*buffer;
	t_command	**commands;
	char		**builtinList;
	int			i;
	
	exit = 0;
	handle_signals();
	// !!
	// PROVISORY CODE FOR BUITIN LIST
	builtinList = (char **)malloc(sizeof(char *) * 10);
	*builtinList = ft_strdup("pwd");
	// !!

	// Checking env
	char **path;
	path = findPath(env);
	
	while (!exit)
	{
		buffer = readline("ft_shell>");
		if (buffer && *buffer)
			add_history(buffer);
		commands = commandList(buffer);
		i = 0;
		// printf("hey1\n");
		while (commands[i])
		{
			// printf("hey2\n");
			commandExec(commands[i], builtinList, path);
			i++;
		}
		free(buffer);
		buffer = (char *)NULL;
	}
	return (0);
}
