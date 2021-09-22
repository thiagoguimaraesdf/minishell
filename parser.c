/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:32:57 by tguimara          #+#    #+#             */
/*   Updated: 2021/09/22 10:59:01 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <fcntl.h>

#include <stdio.h>

void	parse_redirections(t_token **token, t_command **command)
{
	while ((*token) && (*token)->type != IS_PIPE)
	{
		if ((*token)->type == IS_REDIR_IN | (*token)->type == IS_REDIR_IN_2)
		{
			(*command)->redirection_in[0] = ft_strdup((*token)->content);
			(*token) = (*token)->next;
			// necessario criar função para lidar com syntax error
			if ((*token)->type != IS_COMMON)
				break ;
			(*command)->redirection_in[1] = ft_strdup((*token)->content);
			(*token) = (*token)->next;		
		}
		else
		{
			(*command)->redirection_out[0] = ft_strdup((*token)->content);
			(*token) = (*token)->next;
			// necessario criar função para lidar com syntax error
			if ((*token)->type != IS_COMMON)
				break ;
			(*command)->redirection_out[1] = ft_strdup((*token)->content);
			(*token) = (*token)->next;					
		}
	}
}

static int	parse_args(t_token **token, t_command **command)
{
	int		total_args;
	
	total_args = 1;
	while ((*token) && (*token)->type != IS_PIPE && (*token)->type < IS_REDIR)
	{
		(*command)->args[total_args] = ft_strdup((*token)->content);
		total_args++;
		(*token) = (*token)->next;
	}
	return (total_args - 1);
}


/*
	TODO:
	- Necessário verificar se o arquivo é diretorio. Caso seja, retornar no formato:
		bash: /home/tguimara/42sp/projects/minishell: Is a directory
*/
static char	*findExecutable(char *command, char *cur_dir, char **path)
{
	char		*new_command;
	char		*full_path;
	struct stat stat_buf;
	int			i;
	
	i = 0;
	new_command = ft_strjoin("/", command);
	if (!ft_strncmp(command, "./", 2) || !ft_strncmp(command, "/", 1))
	{
		if (stat(command, &stat_buf) < 0)
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
			// printf("full path:%s\n", full_path);
			// printf("path stat%d\n\n", stat(full_path, stat_buf));
			if(stat(full_path, &stat_buf) >= 0)
				return (full_path);
			i++;
		}
	}
	return (NULL);
}

t_command	*init_command(t_token **token, char **builtin_list, char **path)
{
	t_command	*command;
	
	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->exec_path = NULL;
	if (isBuiltin((*token)->content, builtin_list))
			command->builtin = 1;
	else
	{
		command->exec_path = NULL;
		command->exec_path = findExecutable((*token)->content, myPwd(), path);
		if (!command->exec_path)
		{
			ft_printf("%s: command not found\n", (*token)->content);
			free(command);
			return ((t_command *)NULL);
		}
		command->builtin = 0;
	}
	command->command = ft_strdup((const char*)(*token)->content);
	command->args = (char **)ft_calloc(sizeof(char *), 256);
	command->args[0] = ft_strdup(command->command);
	command->total_args = -1;
	command->redirection_in = (char **)ft_calloc(sizeof(char *), 3);
	command->redirection_out = (char **)ft_calloc(sizeof(char *), 3);
	command->has_pipe = -1;
	command->next = NULL;
	(*token) = (*token)->next;
	return (command);
}

static void 	read_tokens()
{
	
}

t_command	*parser(t_pipeline **pipeline, char **builtin_list, char **path)
{
	int			total_args;
	t_token		*token;
	t_command	*command_list;
	t_command	*command;
	int			i;
	
	// init command realiza verificação se comando é builtin ou executável
	token = (*pipeline)->token_list;
	(*pipeline)->total_commands = 1;
	command_list = init_command(&token, builtin_list, path);
	command = command_list;
	if (!command_list)
		return ((t_command *)NULL);
	while (token)
	{
		
		if (token && token->type == IS_PIPE)
		{
			(*pipeline)->total_commands = (*pipeline)->total_commands + 1;
			token = token -> next;
			// syntax error
			if (!token)
				break ;
			if (token)
			{
				command->has_pipe = 1;
				command->next = init_command(&token, builtin_list, path);
				if (!command->next)
					break;
				command = command->next;
			}	
			else
				break ;
		}
		if(!token)
			break ;
		command->total_args = parse_args(&token, &command);
		if (token && token->type >= IS_REDIR)
			parse_redirections(&token, &command);
	}
	return (command_list);
}