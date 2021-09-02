/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandExec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 10:37:11 by tguimara          #+#    #+#             */
/*   Updated: 2021/09/02 16:03:30 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "minishell.h"

#include <stdio.h>

int		pwd(t_command *command)
{
	char 	*cur_path;
	
	cur_path = (char *)malloc(sizeof(char) * 100);
	cur_path = getcwd(cur_path, 100);
	return (printf("%s\n", cur_path));
}


int	commandExec(t_command *command, char **builtinList)
{
	// char	**path;
	char 	*cur_path;
	int		wstatus;
	int		child_pid;
	
	// path = ft_split(PATH, ':');
	// cur_path = (char *)malloc(sizeof(char) * 100);
	// cur_path = getcwd(cur_path, 100);
	/*
		Setting cur_path = \bin\ for tests
	*/
	cur_path = ft_strdup("/usr/bin/");
	if (command->command);
	{
		printf("hey\n");
		child_pid = fork();
		if (child_pid == 0)
		{
			printf("child\n");
			// if (*command->redirection_out)
			// {
			// 	printf("redir\n");
			// 	close(1);
			// 	if (!open(command->redirection_out, O_WRONLY))
			// 		return (-1);
			// }
			printf("path:%s\n", ft_strjoin(cur_path, command->command));
			char *newargv[] = {"ls", NULL};
			execve(ft_strjoin(cur_path, command->command), newargv, NULL);
		}
		else
			wait(&child_pid);
	}
	return (0);	
}