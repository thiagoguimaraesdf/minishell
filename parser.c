/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:32:57 by tguimara          #+#    #+#             */
/*   Updated: 2021/11/21 05:49:46 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
			if ((*token)->type != IS_COMMON)
				break ;
			(*command)->redirection_in[1] = ft_strdup((*token)->content);
			(*token) = (*token)->next;
		}
		else
		{
			(*command)->redirection_out[0] = ft_strdup((*token)->content);
			(*token) = (*token)->next;
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

static int	handle_pipe(t_pipeline **pipeline, t_command **command,
	t_token	**token, t_config *g_shell_config)
{
	(*pipeline)->total_commands = (*pipeline)->total_commands + 1;
	(*token) = (*token)->next;
	if (!(*token))
		return (-1);
	if ((*token))
	{
		(*command)->has_pipe = 1;
		(*command)->next = init_command(token, g_shell_config->builtin_list,
				g_shell_config->path);
		if (!(*command)->next)
			return (-1);
		(*command) = (*command)->next;
	}	
	else
		return (-1);
	return (0);
}

t_command	*parser(t_pipeline **pipeline, t_config *g_shell_config)
{
	int			total_args;
	t_token		*token;
	t_command	*command_list;
	t_command	*command;

	token = (*pipeline)->token_list;
	(*pipeline)->total_commands = 1;
	command_list = init_command(&token, g_shell_config->builtin_list,
			g_shell_config->path);
	command = command_list;
	if (!command)
		return ((t_command *)NULL);
	while (token)
	{
		if (token && token->type == IS_PIPE)
		{
			if (handle_pipe(pipeline, &command, &token, g_shell_config) == -1)
				break ;
		}
		if (!token)
			break ;
		command->total_args = parse_args(&token, &command);
		if (token && token->type >= IS_REDIR)
			parse_redirections(&token, &command);
	}
	return (command_list);
}
