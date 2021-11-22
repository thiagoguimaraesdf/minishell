/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_create.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:47:24 by tguimara          #+#    #+#             */
/*   Updated: 2021/10/18 11:47:50 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*new_env(char *env)
{
	t_env	*env_list;

	env_list = (t_env *)malloc(sizeof(t_env));
	env_list->content = ft_split(env, '=');
	env_list->next = NULL;
	return (env_list);
}

void	env_include(t_env **env_before, char *env)
{
	t_env	*next_env;

	next_env = new_env(env);
	(*env_before)->next = next_env;
}

t_env	*env_init(char **env)
{
	t_env	*env_list;
	t_env	*next;

	if (env && *env)
		env_list = new_env(*env);
	else
		return ((t_env *) NULL);
	env++;
	next = env_list;
	while (env && *env)
	{
		next->next = new_env(*env);
		next = next->next;
		env++;
	}
	g_shell_config->free_list->env = true;
	return (env_list);
}
