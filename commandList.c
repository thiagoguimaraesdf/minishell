/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandList.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:32:57 by tguimara          #+#    #+#             */
/*   Updated: 2021/09/02 22:50:43 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <fcntl.h>

#include <stdio.h>

static int	countArgs(char **tokens)
{
	int	i;

	i = 0;
	while (*(tokens + i) && ft_strncmp(*(tokens + i), ">", 2))
	{
		// printf("token:%s\n", *(tokens + i));
		i++;	
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
	commandList = (t_command **)malloc(1 + sizeof(commands) / sizeof(char *));
	if (!commands)
		return ((t_command **)NULL);
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
		total_args = countArgs(tokens);
		printf("total args:%d\n", total_args);
		if (total_args > 0)
		{
			commandList[i]->args = (char **)malloc((total_args + 2) * sizeof(char *));
			commandList[i]->args[total_args + 1] = NULL;		
		}
		else
		{
			commandList[i]->args = (char **)malloc(sizeof(char *) * 2);
			commandList[i]->args[1] = NULL;
		}				
		commandList[i]->args[0] = commandList[i]->command;
		while (total_args - 1 >= 0)
		{
			commandList[i]->args[total_args] = *(tokens + total_args - 1);
			printf("arg:%s\n", commandList[i]->args[total_args]);
			total_args--;
		}
		tokens = tokens + countArgs(tokens);
		printf("token:%s\n", *tokens);
		commandList[i]->redirection_out = NULL;
		commandList[i]->redirection_in = NULL;		
		if (*tokens && !ft_strncmp(*tokens, ">", 2))
		{
			tokens++;
			commandList[i]->redirection_out = ft_strdup(*tokens);
			printf("redirout:%s\n", commandList[i]->redirection_out);	
		}
		/*
			Dealing with redirections
		*/
		// default setting for in and outfiles
		// (*commandList)->infile = 0;
		// (*commandList)->outfile = 1;
		// if (*tokens)
		// {
		// 	if (ft_strncmp(*tokens, "<", 2))
		// 	{
		// 		close(0);
		// 		tokens++;
		// 		if (*tokens)
		// 		{
		// 			fd = open(*tokens, O_RDONLY);
		// 			if (fd)
		// 				(*commandList)->infile = fd;
		// 		}
		// 		else
		// 			return ((t_command **)NULL);
		// 	}
		// 	else if (ft_strncmp(*tokens, ">", 2))
		// 	{
		// 		close(1);
		// 		tokens++;
		// 		if (*tokens)
		// 		{
		// 			fd = open(*tokens, O_WRONLY);
		// 			if (fd)
		// 				(*commandList)->outfile = fd;
		// 		}	
		// 		else
		// 			return ((t_command **)NULL);				
		// 	}
		// 	else
		// 		return ((t_command **)NULL);
		// }
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