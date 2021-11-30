/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:58:52 by tguimara          #+#    #+#             */
/*   Updated: 2021/11/30 05:11:30 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_export(int total_args, char **args, t_env *env)
{
	int		env_args;
	char	**temp_arg;
	t_env	*cur_env;

	env_args = 1;
	while (args && args[env_args])
	{
		if (!ft_strchr(args[env_args], '='))
			return (no_equal_handler(args[env_args]));
		temp_arg = ft_split(ft_strtrim(args[env_args], "\""), '=');
		if (!ft_isalpha(**temp_arg))
			return (identifier_error(args[env_args], &temp_arg, total_args));
		cur_env = is_env(*temp_arg, env);
		if (cur_env)
			update_env(temp_arg, env);
		else
		{
			cur_env = get_last_env(env);
			env_include(&cur_env, args[env_args]);
			cur_env = get_last_env(env);
		}
		env_args++;
	}
}

/*
	static void	exit_minishell(t_config **shell_config)
	
	A função exit_minishell() é responsável por verificar
	quais partes do program foram alocadas anteriormente
	e chamar os metodos que realizarão o free.
*/
void	exit_minishell(void)
{
	if (g_shell_config->free_list->env == true)
	{
		free_env_list(g_shell_config->env);
		free(g_shell_config->env);
	}
	if (g_shell_config->free_list->bultin == true)
	{
		ft_free_str_array(g_shell_config->builtin_list);
		free(g_shell_config->builtin_list);
	}
	if (g_shell_config->free_list->path == true)
		ft_free_str_array(g_shell_config->path);
	free(g_shell_config->free_list);
	free(g_shell_config);
}

void	my_exit(t_pipeline **pipeline)
{
	g_shell_config->should_continue = false;
	exit(EXIT_NUMBER);
}
