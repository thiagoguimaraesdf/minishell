/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_reads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:32:12 by tguimara          #+#    #+#             */
/*   Updated: 2021/10/07 22:04:17 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_var(char *str, t_token **token, t_env *env, int exit_status)
{
	char		*buffer;
	char		*content;
	int			size;

	buffer = ft_substr(str, 1, end_var_pos(str));
	if (!buffer)
		return (-1);
	if (*buffer == '?')
	{
		content = ft_itoa(exit_status);
		ft_strlcat((*token)->content, content,
			ft_strlen(content) + ft_strlen((*token)->content) + 1);
		free(content);
		size = 2;
	}
	else if (is_env2(env, buffer))
	{
		content = get_env_content(buffer, env);
		ft_strlcat((*token)->content, content,
			ft_strlen(content) + ft_strlen((*token)->content) + 1);
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

int	read_redir(char *str, t_token **token)
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

int	read_token(char *str, t_token **token)
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
