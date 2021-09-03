/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandList.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:32:57 by tguimara          #+#    #+#             */
/*   Updated: 2021/09/03 14:09:25 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <fcntl.h>

#include <stdio.h>

#define REDIR_IN		0
#define REDIR_OUT		2
#define REDIR_OUT_2		3
#define REDIR_IN_2		1
#define ERROR			-1

static int	isRedirection(char *token)
{
	if (!ft_strncmp(token, ">", 1))
		return (REDIR_OUT);
	else if (!ft_strncmp(token, "<", 1))
		return (REDIR_IN);
	else if (!ft_strncmp(token, ">>", 2))		
		return (REDIR_OUT_2);
	else if (!ft_strncmp(token, "<<", 2))	
		return (REDIR_IN_2);
	else
		return (ERROR);
}
static int	handleRedir(char **tokens, t_command *commandList)
{
	int	redir_return;

	// printf("inside token:%s\n", *tokens);
	redir_return = isRedirection(*tokens);
	if (*tokens && redir_return >= 0)
	{
		tokens++;
		if (!(*tokens))
			return (-1);
		if (redir_return > 1)
			commandList->redirection_out = ft_strdup(*tokens);
		else
			commandList->redirection_in = ft_strdup(*tokens);
		return (1);
	}
	return (0);
}

static int	handleArgs(char **tokens, t_command *commandList)
{
	int	i;
	int total_args;

	i = 0;
	while (*(tokens + i) && isRedirection(*(tokens + i)) == ERROR)
		i++;
	total_args = i;
	commandList->args = (char **)malloc((i + 2) * sizeof(char *));
	commandList->args[0] = commandList->command;
	commandList->args[i + 1] = NULL;
	while (total_args - 1 >= 0)
	{
		commandList->args[total_args] = *(tokens + total_args - 1);
		printf("arg:%s\n", commandList->args[total_args]);
		total_args--;
	}
	return (i);
}

t_command	**commandList(char *buffer)
{
	int			total_args;
	char 		**commands;
	char		**tokens;
	t_command	**commandList;
	int			i;
	
	commands = ft_split(buffer, '|');
	if (!commands)
		return ((t_command **)NULL);
	commandList = (t_command **)malloc(1 + sizeof(commands) / sizeof(char *));
	i = 0;
	while (commands && *commands)
	{
		tokens = ft_split(*commands, ' ');
		if (!(*tokens))
			break ;
		commandList[i] = (t_command *)malloc(sizeof(t_command));
		commandList[i]->command = ft_strdup(*tokens);
	 	printf("command:%s\n", *tokens);
		tokens++;
		total_args = handleArgs(tokens, commandList[i]);
		printf("total args:%d\n", total_args);
		tokens = tokens + total_args;
		printf("token:%s\n", *tokens);
		// JOGAR LINHAS ABAIXO PARA UM COMMAND_LIST INIT
		commandList[i]->redirection_out = NULL;
		commandList[i]->redirection_in = NULL;
		if (*tokens)
		{
			if (!handleRedir(tokens, *commandList))
				return ((t_command **)NULL);			
		}
		printf("floop\n");
		commands++;
		i++;
		// free(tokens);
		// tokens = NULL;
	}
	commandList[i] = NULL;
	// free(commands);
	// commands = NULL;
	return (commandList);
}