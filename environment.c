/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:40:48 by tguimara          #+#    #+#             */
/*   Updated: 2021/10/07 21:52:35 by tguimara         ###   ########.fr       */
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

t_env	*get_last_env(t_env *env)
{
	t_env	*last;

	if (env == NULL)
		return (NULL);
	last = env;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

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

t_env	*is_env(char *name, t_env *env)
{
	size_t	name_size;

	name_size = ft_strlen(name);
	while (env && env->content[0])
	{
		if (ft_strlen(env->content[0]) == name_size)
		{
			if (!ft_strncmp(name, env->content[0], name_size))
				return (env);
		}
		env = env->next;
	}
	return ((t_env *) NULL);
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

void	env_include(t_env **env_before, char *env)
{
	t_env	*next_env;

	next_env = new_env(env);
	(*env_before)->next = next_env;
}

size_t	env_size(t_env	*env_list)
{
	size_t	size;

	size = 0;
	while (env_list)
	{
		env_list = env_list->next;
		size++;
	}
	return (size);
}

t_env	*env_init(char **env, t_free	*error_list)
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
	error_list->env = true;
	return (env_list);
}

char	**t_env_to_array(t_env *env_list)
{
	char	**env_array;
	int		i;

	env_array = (char **)malloc(sizeof(char *) * env_size(env_list) + 1);
	i = 0;
	while (env_list)
	{
		//!!!!!
		//Vamos precisar d eum strjoin aqui que coloque tabmbem um separador entre as str
		env_array[i] = ft_strjoin(env_list->content[0], env_list->content[1]);
		i++;
		env_list = env_list->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

/*
	static void	free_env_list(t_env **env_list)
	
	A função free_env_list() é responsável por dar free
	em todas as variáveis mallocadas na struct t_env,
	inicializadas no programa main() por meio das funções
	init_minishell() > env_init().
	A função env_init() está no arquivo environment.c
*/
void	free_env_list(t_env **env_list)
{
	t_env	*aux;
	t_env	*temp;

	if (env_list == NULL)
		return ;
	aux = *env_list;
	while (aux != NULL)
	{
		temp = aux->next;
		ft_free_str_array(aux->content);
		free(aux->content);
		aux->content = NULL;
		aux = NULL;
		aux = temp;
	}
	*env_list = NULL;
}
