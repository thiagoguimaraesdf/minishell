/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:42:53 by tguimara          #+#    #+#             */
/*   Updated: 2021/11/30 05:12:01 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	char	**t_env_to_array(t_env *env_list)
	
	Converter variável do tipo t_env (linked list) em
	array.
	Obs: Vamos precisar d eum strjoin aqui que coloque tambem
	um separador entre as str
*/
char	**t_env_to_array(t_env *env_list)
{
	char	**env_array;
	char	*temp;
	int		i;

	env_array = (char **)malloc(sizeof(char *) * env_size(env_list) + 1);
	i = 0;
	while (env_list)
	{
		temp = ft_strjoin(env_list->content[0], "=");
		env_array[i] = ft_strjoin(temp, env_list->content[1]);
		if (temp)
			free(temp);
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
void	free_env_list(t_env *env_list)
{
	t_env	*aux;
	t_env	*temp;

	if (env_list == NULL)
		return ;
	aux = env_list;
	while (aux != NULL)
	{
		temp = aux->next;
		ft_free_str_array(aux->content);
		free(aux->content);
		aux->content = NULL;
		aux = NULL;
		aux = temp;
	}
	env_list = NULL;
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
