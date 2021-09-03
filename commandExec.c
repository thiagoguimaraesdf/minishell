/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandExec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 10:37:11 by tguimara          #+#    #+#             */
/*   Updated: 2021/09/03 14:33:03 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "minishell.h"

#include <stdio.h>

char	*pwd(void)
{
	char 	*cur_dir;
	
	cur_dir = (char *)malloc(sizeof(char) * 100);
	cur_dir = getcwd(cur_dir, 100);
	return (cur_dir);
}

static char	*findExecutable(char *command, char *cur_dir, char **path)
{
	char		*new_command;
	char		*full_path;
	struct stat *stat_buf;
	int			i;
	
	i = 0;
	new_command = ft_strjoin("/", command);
	if (!ft_strncmp(command, "./", 2) || !ft_strncmp(command, "/", 1))
	{
		if (stat(command, stat_buf) < 0)
		{
			ft_printf("-minishell: %s: No such file or directory\n", command);
			return (NULL);
		}
		return (command);
	}
	else
	{
		while (path[i])
		{
			// necessario dar free neste full_path
			full_path = ft_strjoin(path[i], new_command);
			printf("full path:%s\n", full_path);
			printf("path stat%d\n\n", stat(full_path, stat_buf));
			if(stat(full_path, stat_buf) >= 0)
				return (full_path);
			i++;
		}
	}
	return (NULL);
}

int	commandExec(t_command *command, char **builtinList, char **path)
{
	// char	**path;
	int		wstatus;
	int		child_pid;
	char	*exec_path;
	
	// path = ft_split(PATH, ':');
	// cur_path = (char *)malloc(sizeof(char) * 100);
	// cur_path = getcwd(cur_path, 100);
	/*
		Setting cur_path = \bin\ for tests
	*/
	if (command->command);
	{
		printf("commandExec Begin\n");
		exec_path = findExecutable(command->command, pwd(), path);
		printf("exec path:%s\n", exec_path);
		if (!(*exec_path))
			return (-1);
		child_pid = fork();
		if (child_pid == 0)
		{
			printf("child\n");
			if (command->redirection_out && *command->redirection_out)
			{
				printf("redir_out\n");
				close(1);
				if (open(command->redirection_out, O_WRONLY) < 0)
					exit(-1);
			}
			if (command->redirection_in && *command->redirection_in)
			{
				close(0);
				if (open(command->redirection_in, O_RDONLY) < 0)
					exit(-1);
			}
			execve(exec_path, command->args, NULL);
		}
		else
		{	
			wait(&child_pid);
			printf("back to shell\n");
		}
	}
	return (0);	
}