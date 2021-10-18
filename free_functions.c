/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:52:30 by tguimara          #+#    #+#             */
/*   Updated: 2021/10/18 11:58:11 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_token_list(t_token **token_list)
{
	t_token	*temp_token;

	temp_token = *token_list;
	while (temp_token)
	{
		if ((*token_list)->content)
			free((*token_list)->content);
		(*token_list)->content = NULL;
		temp_token = (*token_list);
		(*token_list) = temp_token->next;
		free(temp_token);
		temp_token = NULL;
	}
}

static void	free_redirections(t_command **command_list)
{
	if ((*command_list)->redirection_in)
	{
		if ((*command_list)->redirection_in[0])
			free((*command_list)->redirection_in[0]);
		if ((*command_list)->redirection_in[1])
			free((*command_list)->redirection_in[1]);
		free((*command_list)->redirection_in);
		(*command_list)->redirection_in[0] = NULL;
		(*command_list)->redirection_in[1] = NULL;
		(*command_list)->redirection_in = NULL;
	}
	if ((*command_list)->redirection_out)
	{
		if ((*command_list)->redirection_out[0])
			free((*command_list)->redirection_out[0]);
		if ((*command_list)->redirection_out[1])
			free((*command_list)->redirection_out[1]);
		free((*command_list)->redirection_out);
		(*command_list)->redirection_out[0] = NULL;
		(*command_list)->redirection_out[1] = NULL;
		(*command_list)->redirection_out = NULL;
	}
}

/*
	static void	free_command_list(t_command **command_list)

	A função free_command_list() é responsável por dar free
	em todas as variáveis mallocadas na struct t_command, 
	inicializadas no programa main() pela função parser().
	A struct t_command fica armanezada na struct t_pipeline.
*/
static void	free_command_list(t_command **command_list)
{
	t_command	*temp_command;

	if (!command_list)
		return ;
	while (*command_list)
	{
		if ((*command_list)->command)
			free((*command_list)->command);
		(*command_list)->command = NULL;
		if ((*command_list)->exec_path)
			free((*command_list)->exec_path);
		(*command_list)->exec_path = NULL;
		ft_free_str_array((*command_list)->args);
		free((*command_list)->args);
		free_redirections(command_list);
		temp_command = (*command_list);
		(*command_list) = temp_command->next;
		free(temp_command);
		temp_command = NULL;
	}
}

/*
	static void	free_pipeline(t_pipeline **pipeline)
	
	A função free_pipeline() é responsável por dar free
	em todas as variáveis mallocadas na struct t_pipeline,
	inicializadas no programa main().
*/
void	free_pipeline(t_pipeline **pipeline)
{
	if (!(*pipeline))
		return ;
	// if((*pipeline)->buffer)
	// 	free((*pipeline)->buffer);
	// (*pipeline)->buffer = NULL;
	if ((*pipeline)->token_list)
		free_token_list(&(*pipeline)->token_list);
	if ((*pipeline)->command_list)
		free_command_list(&(*pipeline)->command_list);
	free(*pipeline);
	(*pipeline) = NULL;
}

/*
	static void	free_config(t_pipeline **shell_config)
	
	A função free_config() é responsável por dar free
	em todas as variáveis mallocadas na struct t_config,
	inicializadas no programa main().
*/
void	free_config(void)
{	
	if (!g_shell_config)
		return ;
	ft_free_str_array(g_shell_config->builtin_list);
	ft_free_str_array(g_shell_config->path);
	free_env_list(g_shell_config->env);
}
