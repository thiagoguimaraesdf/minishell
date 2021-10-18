/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:30:54 by tguimara          #+#    #+#             */
/*   Updated: 2021/10/18 16:28:08 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	TODO:
	- Necessário verificar se o arquivo é diretorio. Caso seja, retornar no formato:
		bash: /home/tguimara/42sp/projects/minishell: Is a directory
*/
static char	*find_executable(char *command, char *cur_dir, char **path)
{
	char		*new_command;
	char		*full_path;
	struct stat	stat_buf;
	int			i;

	i = 0;
	new_command = ft_strjoin("/", command);
	if (!ft_strncmp(command, "./", 2) || !ft_strncmp(command, "/", 1))
	{
		if (stat(command, &stat_buf) < 0)
			ft_printf("-minishell: %s: No such file or directory\n", command);
		return (command);
	}
	else
	{
		while (path[i])
		{
			full_path = ft_strjoin(path[i], new_command);
			if (stat(full_path, &stat_buf) >= 0)
				return (full_path);
			i++;
		}
	}
	return (NULL);
}

static int	init_command_helper(t_command **command, char *content)
{
	(*command)->command = ft_strdup((const char *)content);
	(*command)->args = (char **)ft_calloc(sizeof(char *), 256);
	(*command)->args[0] = ft_strdup((*command)->command);
	(*command)->total_args = -1;
	(*command)->redirection_in = (char **)ft_calloc(sizeof(char *), 3);
	(*command)->redirection_out = (char **)ft_calloc(sizeof(char *), 3);
	(*command)->has_pipe = -1;
	(*command)->next = NULL;
	return (0);
}

t_command	*init_command(t_token **token, char **builtin_list, char **path)
{
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->exec_path = NULL;
	if (is_builtin((*token)->content, builtin_list))
		command->builtin = 1;
	else
	{
		command->exec_path = find_executable((*token)->content, my_pwd(), path);
		if (!command->exec_path)
		{
			ft_printf("%s: command not found\n", (*token)->content);
			free(command);
			return ((t_command *) NULL);
		}
		command->builtin = 0;
	}
	init_command_helper(&command, (*token)->content);
	(*token) = (*token)->next;
	return (command);
}
