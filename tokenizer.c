/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:32:12 by tguimara          #+#    #+#             */
/*   Updated: 2021/10/07 06:37:48 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_token	*init_token(int type, char *content)
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

static int	is_env(t_env *env, char *str)
{
	while (env)
	{
		if (!ft_strncmp(env->content[0], str, ft_strlen(str)))
			return (1);
		env = env->next;
	}
	return (0);
}

static int	end_var_pos(char *str)
{
	int	i;

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

char	*get_env_content(char *name, t_env *env)
{
	t_env	*temp_env;	

	temp_env = env;
	while (temp_env)
	{
		if (!ft_strncmp(temp_env->content[0], name, ft_strlen(name)))
			return (temp_env->content[1]);
		temp_env = temp_env->next;
	}
	return (NULL);
}

static int	expand_var(char *str, t_token **token, t_env *env, int exit_status)
{
	char		*buffer;
	char		*content;
	int			dest_size;
	int			size;

	buffer = ft_substr(str, 1, end_var_pos(str));
	if (!buffer)
		return (-1);
	size = -1;
	dest_size = ft_strlen((*token)->content);
	if (*buffer == '?')
	{
		content = ft_itoa(exit_status);
		ft_strlcat((*token)->content, content,
			ft_strlen(content) + dest_size + 1);
		free(content);
		size = 2;
	}
	else if (is_env(env, buffer))
	{
		content = get_env_content(buffer, env);
		ft_strlcat((*token)->content, content,
			ft_strlen(content) + dest_size + 1);
		size = ft_strlen(buffer) + 1;
	}
	free(buffer);
	return (size);
}

int	read_string(char *str, t_token **token, t_env *env, int exit_status)
{
	int		i;
	int		size;

	size = 0;
	i = 1;
	while (str[i] != str[0])
	{
		if (str[i] == '$' && str[0] == '\"')
		{	
			i += expand_var(str + i, token, env, exit_status);
			continue ;
		}
		(*token)->content[i - 1] = str[i];
		i++;
	}
	return (i + 1);
}

static int	read_redir(char *str, t_token **token)
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

static int	read_token(char *str, t_token **token)
{
	int	i;
	int	type;

	i = 0;
	type = token_type(str[i]);
	(*token)->type = type;
	while (str && str[i])
	{
		if (type != IS_COMMON)
			return (i);
		(*token)->content[i] = str[i];
		i++;
		type = token_type(str[i]);
	}
	return (i);
}

size_t	read_pipe(t_token **token)
{
	ft_strlcat((*token)->content, "|", 2);
	(*token)->type = IS_PIPE;
	return (1);
}

size_t	token_router(char *buffer, t_token **token, t_env *env, int exit_status)
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
