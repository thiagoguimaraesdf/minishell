/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:40:48 by tguimara          #+#    #+#             */
/*   Updated: 2021/10/18 11:49:45 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env2(t_env *env, char *str)
{
	while (env)
	{
		if (!ft_strncmp(env->content[0], str, ft_strlen(str)))
			return (1);
		env = env->next;
	}
	return (0);
}

void	update_env(char **temp_arg, t_env *env)
{
	t_env	*temp_env;

	temp_env = env;
	if (temp_arg && temp_arg[1])
	{
		while (ft_strncmp(temp_env->content[0],
				temp_arg[0], ft_strlen(temp_arg[0])))
			temp_env = temp_env->next;
		if (temp_env->content[1])
			free(temp_env->content[1]);
		temp_env->content[1] = ft_strdup(temp_arg[1]);
	}
	free(temp_arg[0]);
	if (temp_arg[1])
		free(temp_arg[1]);
	free(temp_arg);
	temp_arg = NULL;
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

void	env_print(t_env *env)
{
	write(1, env->content[0], ft_strlen(env->content[0]));
	write(1, "=", 1);
	if (env->content[1])
	{
		write(1, env->content[1], ft_strlen(env->content[1]));
	}
	write(1, "\n", 1);
}

void	env_delete(t_env **env, t_env **env_before)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = *env_before;
	while ((*env) && (*env)->content[i])
	{
		free((*env)->content[i]);
		(*env)->content[i] = NULL;
		i++;
	}
	temp->next = (*env)->next;
	free(*env);
}
