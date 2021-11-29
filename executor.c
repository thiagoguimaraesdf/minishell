/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 10:37:11 by tguimara          #+#    #+#             */
/*   Updated: 2021/11/29 15:13:13 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "minishell.h"

#define TEMP_PATH "./temp"

static void	exec_builtin(t_pipeline **pipeline)
{
	t_command	*command;
	t_env		*env;

	command = (*pipeline)->command_list;
	if (!ft_strncmp(command->command, "pwd", 3))
		my_pwd();
	else if (!ft_strncmp(command->command, "env", 3))
		my_env(command->total_args, command->args, g_shell_config->env);
	else if (!ft_strncmp(command->command, "export", 6))
		my_export(command->total_args, command->args, g_shell_config->env);
	else if (!ft_strncmp(command->command, "unset", 5))
		my_unset(command->total_args, command->args, g_shell_config->env);
	else if (!ft_strncmp(command->command, "cd", 2))
		my_cd(command->total_args, command->args);
	else if (!ft_strncmp(command->command, "echo", 4))
		my_echo(command->args);
	else if (!ft_strncmp(command->command, "exit", 4))
		my_exit(pipeline);
	exit(0);
}

static int	read_from_source(t_command *command)
{
	char	*buffer;
	size_t	keyword_size;
	int		fd;

	keyword_size = ft_strlen(command->redirection_in[1]);
	fd = open(TEMP_PATH, O_WRONLY | O_TRUNC | O_CREAT);
	while (1)
	{
		buffer = readline("> ");
		if (!ft_strncmp(command->redirection_in[1], buffer, keyword_size))
			break ;
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
	}
	if (buffer)
		free(buffer);
	close(fd);
	return (open(TEMP_PATH, O_RDONLY));
}

/*
	bug 1: cat << oi > text.xt
	bug 2: ls | cat > text.xt
*/
static void	handle_redirection(t_command *command)
{
	int	redir_file;

	if (command->redirection_out && command->redirection_out[0])
	{
		if (!ft_strncmp(command->redirection_out[0], ">>", 2))
			redir_file = open(command->redirection_out[1],
					O_WRONLY | O_CREAT | O_APPEND);
		else
			redir_file = open(command->redirection_out[1],
					O_WRONLY | O_CREAT | O_TRUNC);
		dup2(redir_file, 1);
		close(redir_file);
	}
	if (command->redirection_in && command->redirection_in[0])
	{
		if (!ft_strncmp(command->redirection_in[0], "<", 2))
			redir_file = open(command->redirection_in[1], O_RDONLY | O_CREAT);
		else
			redir_file = read_from_source(command);
		dup2(redir_file, 0);
		close(redir_file);
		if (!ft_strncmp(command->redirection_in[0], "<<", 2))
			unlink(TEMP_PATH);
	}	
}

static void	handle_pipe(t_command *command)
{
	static int	fd[2];
	static int	come_from_pipe;

	if (command->has_pipe == 1)
	{
		if (come_from_pipe)
		{
			dup2(fd[0], 0);
			close(fd[0]);
		}
		pipe(fd);
		dup2(fd[1], 1);
		close(fd[1]);
		come_from_pipe = 1;
	}
	else
	{
		dup2(g_shell_config->stdout, 1);
		dup2(fd[0], 0);
		close(fd[0]);
	}
}

void	exec(t_pipeline **pipeline)
{
	int			child_pid;
	t_command	*command;

	command = (*pipeline)->command_list;
	while (command)
	{
		if ((*pipeline)->total_commands > 1)
			handle_pipe(command);
		child_pid = fork();
		if (child_pid == 0)
		{
			handle_redirection(command);
			if (command->builtin)
				exec_builtin(pipeline);
			else
				execve(command->exec_path, command->args,
					t_env_to_array(g_shell_config->env));
		}
		else
		{
			waitpid(child_pid, &g_shell_config->last_exit_status, 0);
			dup2(g_shell_config->stdin, 0);
			dup2(g_shell_config->stdout, 1);
		}
		command = command->next;
	}
}
