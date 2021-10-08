/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:32:12 by tguimara          #+#    #+#             */
/*   Updated: 2021/10/07 22:00:16 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*init_token(int type, char *content);
static size_t	token_router(char *buffer, t_token **token,
					t_env *env, int exit_status);

/* 
	t_token	*tokenizer(char *buffer, t_env *env, int exit_status)
    
	A função find_path() é separar e rotular cada token disponível
	no input do usuário. As definições dos tokens podem ser encontradas
	na função token_type(), logo abaixo.                                                                    
*/
t_token	*tokenizer(char *buffer, t_env *env, int exit_status)
{
	int			type;
	t_token		*token_list;
	t_token		*token;

	token_list = init_token(IS_INVALID, NULL);
	token = token_list;
	while (buffer && *buffer)
	{
		type = token_type(*buffer);
		if (type == IS_SPACE && buffer++)
			continue ;
		if (type == IS_UNSPECIFIED)
			break ;
		token->type = type;
		buffer = buffer + token_router(buffer, &token, env, exit_status);
		if (buffer && *buffer)
			token->next = init_token(IS_INVALID, NULL);
		if (token->next)
			token = token->next;
	}
	return (token_list);
}

int	token_type(char c)
{
	if (c == '<' | c == '>')
		return (IS_REDIR);
	else if (c == '|')
		return (IS_PIPE);
	else if (c == '$')
		return (IS_VAR);
	else if (c == '\"')
		return (IS_QUOTE);
	else if (c == '\'')
		return (IS_SINGLE_QUOTE);
	else if (c == ' ')
		return (IS_SPACE);
	else if (c == '\\' | c == ';' | c == '&')
		return (IS_UNSPECIFIED);
	else
		return (IS_COMMON);
}

static t_token	*init_token(int type, char *content)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (content && *content)
		token->content = ft_strdup(content);
	else
		token->content = (char *)calloc(1, 256);
	token->next = NULL;
	return (token);
}

static size_t	token_router(char *buffer, t_token **token,
					t_env *env, int exit_status)
{
	size_t	size;
	int		type;

	type = token_type(*buffer);
	size = -1;
	if (type == IS_REDIR)
		size = read_redir(buffer, token);
	else if (type == IS_QUOTE | type == IS_SINGLE_QUOTE)
		size = read_string(buffer, token, env, exit_status);
	else if (type == IS_VAR)
		size = expand_var(buffer, token, env, exit_status);
	else if (type == IS_PIPE)
		size = read_pipe(token);
	else if (type == IS_COMMON)
		size = read_token(buffer, token);
	return (size);
}
