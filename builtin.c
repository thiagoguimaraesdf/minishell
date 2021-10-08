/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 10:02:26 by tguimara          #+#    #+#             */
/*   Updated: 2021/10/07 22:07:42 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_pwd(void)
{
	char	*cur_dir;

	cur_dir = (char *)malloc(sizeof(char) * 100);
	if (!cur_dir)
		return ((char *) NULL);
	cur_dir = getcwd(cur_dir, 100);
	write(1, cur_dir, ft_strlen(cur_dir));
	write(1, "\n", 1);
	return (cur_dir);
}

void	my_echo(char **args)
{
	int	i;
	int	newline;

	newline = 1;
	i = 0;
	args++;
	if (args && !ft_strncmp(*args, "-n", ft_strlen(*args)))
	{
		newline = 0;
		i++;
	}
	while (args && args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		i++;
		if (args[i])
			write(1, " ", 1);
	}
	if (newline)
		write(1, "\n", 1);
}

void	my_cd(int total_args, char **args)
{
	int	chdir_return;

	if (!total_args)
		return ;
	else if (total_args > 1)
	{
		write(1, "-myshell: cd: too many arguments", 32);
		return ;
	}
	// INCLUIR -bash: cd: dsadas: No such file or directory CASO DIRETORIO NAO EXISTA
	if (args && args[1])
		chdir_return = chdir((const char *)args[1]);
}

void	my_env(int total_args, char **args, t_env *env)
{
	t_env	*temp_env;

	temp_env = env;
	if (total_args > 0)
		ft_printf("env: ‘%s’: No such file or directory", *args);
	while (temp_env)
	{
		env_print(temp_env);
		temp_env = temp_env->next;
	}
}

void	my_unset(int total_args, char **args, t_env **env)
{
	t_env	*last_env;
	t_env	*temp_env;

	if (!total_args)
		return ;
	args++;
	temp_env = *env;
	while (args && *args)
	{
		while (temp_env)
		{
			if (!ft_strncmp(*args, temp_env->content[0], ft_strlen(*args)))
			{	
				printf("delete:%s\n", temp_env->content[0]);
				env_delete(&temp_env, &last_env);
				break ;
			}
			last_env = temp_env;
			temp_env = temp_env->next;
		}
		args++;
	}
}

void	identifier_error(char *str, char ***temp_arg, int total_args)
{
	ft_printf("minishell: export: `%s': not a valid identifier\n", str);
	while (*temp_arg && **temp_arg)
		free(**temp_arg++);
	free(*(temp_arg - total_args));
	return ;
}

void	no_equal_handler(char *str)
{
	if (!ft_isalpha(str[0]))
		ft_printf("minishell: export: `%s': not a valid identifier\n", str);
}

void	my_export(int total_args, char **args, t_env **env)
{
	int		env_args;
	char	**temp_arg;
	t_env	*cur_env;

	env_args = 1;
	printf("hey\n");
	while (args && args[env_args])
	{
		if (!ft_strchr(args[env_args], '='))
			return (no_equal_handler(args[env_args]));
		temp_arg = ft_split(ft_strtrim(args[env_args], "\""), '=');
		if (!ft_isalpha(**temp_arg))
			return (identifier_error(args[env_args], &temp_arg, total_args));
		cur_env = is_env(*temp_arg, *env);
		if (cur_env)
			update_env(temp_arg, env);
		else
		{
			printf("include:%s\n", args[env_args]);
			cur_env = get_last_env(*env);
			printf("after:%s\n", cur_env->content[0]);
			env_include(&cur_env, args[env_args]);
			cur_env = get_last_env(*env);
			printf("new_last_env:%s\n", cur_env->content[0]);
		}
		env_args++;
	}
}

/*

*/
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

/*

*/
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
void	free_config(t_config **shell_config)
{	
	if (!(*shell_config))
		return ;
	ft_free_str_array((*shell_config)->builtin_list);
	ft_free_str_array((*shell_config)->path);
	free_env_list(&(*shell_config)->env);
	free(*shell_config);
	(*shell_config) = NULL;
}

/*
	static void	exit_minishell(t_config **shell_config)
	
	A função exit_minishell() é responsável por verificar
	quais partes do program foram alocadas anteriormente
	e chamar os metodos que realizarão o free.
*/
void	exit_minishell(t_config *shell_config)
{
	if (shell_config->free_list->env == true)
	{
		free_env_list(&shell_config->env);
		free(shell_config->env);
	}
	if (shell_config->free_list->bultin == true)
	{
		ft_free_str_array(shell_config->builtin_list);
		free(shell_config->builtin_list);
	}
	if (shell_config->free_list->path == true)
		ft_free_str_array(shell_config->path);
	free(shell_config->free_list);
	free(shell_config);
}

void	my_exit(t_config **shell_config, t_pipeline **pipeline)
{
	if (*pipeline)
		free_pipeline(pipeline);
	if (*shell_config)
		free_config(shell_config);
	exit(1);
}
