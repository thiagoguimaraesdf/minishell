/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:32:12 by tguimara          #+#    #+#             */
/*   Updated: 2021/09/21 14:48:59 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		tokenType(char c)
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

t_token	*initToken(int type, char *content)
{
	t_token *token;
	
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

static int 	isEnv(t_env *env, char *str)
{
	while (env)
	{
		if (!ft_strncmp(env->content[0], str, ft_strlen(str)))
			return (1);
		env = env->next;
	}
	return (0);
}


static int	endVarPos(char *str)
{
	int 	i;

	i = 1;
	while (str && str[i])
	{
		if (str[i] == '\"' | str[i] == '\'' | str[i] == '$' | str[i] == ' ')
		{
			return (i - 1);
		}
		i++;
	}
	return (i - 1);
}

const char	*getEnvContent(char *name, t_env *env)
{
	t_env	*temp_env;	

	temp_env = env;
	while (temp_env)
	{
		if (!ft_strncmp(temp_env->content[0], name, ft_strlen(name)))
			return ((const char *)temp_env->content[1]);		
		temp_env = temp_env->next;	
	}
	return ((const char *)NULL);
}

static int	expandVar(char *str, t_token **token, t_env *env)
{
	char		*buffer;
	const char	*content;
	char 		*temp;
	int			is_env;
	
	buffer = ft_substr(str, 1, endVarPos(str));
	if (!buffer)
		return (-1);
	is_env = isEnv(env, buffer);
	if (is_env)
	{
		content = getEnvContent(buffer, env);
		ft_strlcat((*token)->content, content, ft_strlen(content) + 1);
		return (ft_strlen(buffer) + 1);
	}
	return (-1);
}

int		readString(char *str, t_token **token, t_env *env)
{
	int		i;
	int		size;
	
	size = 0;
	i = 1;
	while (str[i] != str[0])
	{
		if (str[i]  == '$' && str[0] == '\"')
		{	
			i+=expandVar(str + i, token, env);
			continue ;
		}
		(*token)->content[i - 1] = str[i];
		i++;
	}
	return (i + 1);
}

static int	readRedir(char *str, t_token **token)
{
	if (*str == '<')
	{
		if ((str + 1) && *(str + 1) == '<')
		{
			(*token)->type = IS_REDIR_IN_2;
			ft_strlcat((*token)->content, "<<", 3);
			return (2);
		}
		(*token)->type = IS_REDIR_IN;
		ft_strlcat((*token)->content, "<", 2);
	}
	else
	{
		if ((str + 1) && *(str + 1) == '>')
		{
			(*token)->type = IS_REDIR_OUT_2;
			ft_strlcat((*token)->content, ">>", 3);
			return (2);
		}
		(*token)->type = IS_REDIR_OUT;
		ft_strlcat((*token)->content, ">", 2);
	}
	return (1);
}

static int	readToken(char *str, t_token **token)
{
	int	i;
	int type;
		
	i = 0;
	type = tokenType(str[i]);
	(*token)->type = type;
	while(str && str[i])
	{
		if (type != IS_COMMON)
			return (i);
		(*token)->content[i] = str[i];
		i++;
		type = tokenType(str[i]);
	}
	return (i);
}

size_t	readPipe(t_token **token)
{
		ft_strlcat((*token)->content, "|", 2);
		(*token)->type = IS_PIPE;
		return (1);
}

size_t	tokenRouter(char *buffer, t_token **token, t_env *env)
{
	size_t	size;
	int		type;

	type = tokenType(*buffer);
	size = -1;
	if (type == IS_REDIR)
		size = readRedir(buffer, token);
	else if (type == IS_QUOTE | type == IS_SINGLE_QUOTE)
		size = readString(buffer, token, env);
	else if (type == IS_VAR)
		size = expandVar(buffer, token, env);
	else if (type == IS_PIPE)
		size = readPipe(token);
	else if (type == IS_COMMON)
		size = readToken(buffer, token);
	return (size);	
}

t_token		*tokenizer(char *buffer, t_env *env)
{
	int			type;
	t_token		*token_list;
	t_token		*token;
	
	token_list = initToken(IS_INVALID, NULL);
	token = token_list;
	while (buffer && *buffer)
	{
		type = tokenType(*buffer);
		if (type == IS_SPACE && buffer++)
			continue;
		if (type == IS_UNSPECIFIED)
			break;
		token->type = type;
		buffer = buffer + tokenRouter(buffer, &token, env);
		if (buffer && *buffer)
			token->next = initToken(IS_INVALID, NULL);
		if (token->next)
			token = token->next;
	}
	return (token_list);
}