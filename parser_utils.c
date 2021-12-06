/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:30:54 by tguimara          #+#    #+#             */
/*   Updated: 2021/12/06 10:56:33 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_valid_path(char *command)
{
	struct stat	stat_buf;

	if (stat(command, &stat_buf) < 0)
	{
		ft_printf("-minishell: %s: No such file or directory\n", command);
		g_shell_config->last_exit_status = 127;
	}	
	else if (stat_buf.st_mode & __S_IFDIR)
	{
		ft_printf("bash: %s: Is a directory\n", command);
		g_shell_config->last_exit_status = 126;
	}
	return (command);
}

static char	*find_executable(char *command, char **path)
{
	char		*new_command;
	char		*full_path;
	struct stat	stat_buf;
	int			i;

	i = 0;
	if (!ft_strncmp(command, "./", 2) || !ft_strncmp(command, "/", 1))
		return (check_valid_path(command));
	else
	{
		new_command = ft_strjoin("/", command);
		while (path[i])
		{
			full_path = ft_strjoin(path[i], new_command);
			if (stat(full_path, &stat_buf) >= 0)
			{
				free(new_command);
				return (full_path);
			}
			free(full_path);
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

static t_command	*print_and_return(char **path, t_token **token)
{
	if (!path)
		ft_printf("%s: command not found\n", (*token)->content);
	return ((t_command *) NULL);
}

t_command	*init_command(t_token **token, char **builtin_list, t_env *env)
{
	t_command	*command;
	char		**path;

	command = (t_command *)malloc(sizeof(t_command));
	path = ft_split(get_env_content("PATH", env), ':');
	if (!command || !path)
		return (print_and_return(path, token));
	command->exec_path = NULL;
	if (is_builtin((*token)->content, builtin_list))
		command->builtin = 1;
	else
	{
		command->exec_path = find_executable((*token)->content, path);
		if (!command->exec_path)
		{
			ft_printf("%s: command not found\n", (*token)->content);
			g_shell_config->last_exit_status = 127;
			free(command);
			return ((t_command *) NULL);
		}
		command->builtin = 0;
	}
	init_command_helper(&command, (*token)->content);
	(*token) = (*token)->next;
	return (command);
}
