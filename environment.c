/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:40:48 by tguimara          #+#    #+#             */
/*   Updated: 2021/09/29 07:22:44 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*newEnv(char *env)
{
	t_env	*env_list;
	
	env_list = (t_env *)malloc(sizeof(t_env));
	env_list->content = ft_split(env, '=');
	env_list->next = NULL;
	return (env_list);
}

t_env			*getLastEnv(t_env *env)
{
	t_env	*last;

	if (env == NULL)
		return (NULL);
	last = env;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void 			envPrint(t_env *env)
{
	write(1, env->content[0], ft_strlen(env->content[0]));
	write(1, "=", 1);
	if (env->content[1])
	{
		write(1, env->content[1], ft_strlen(env->content[1]));				
	}
	write(1, "\n", 1);
}

void		envDelete(t_env **env, t_env **env_before)
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

void 			envInclude(t_env **env_before, char *env)
{
	t_env 	*new_env;

	new_env = newEnv(env);
	(*env_before)->next = new_env;
}


size_t 		env_size(t_env	*env_list)
{
	size_t 	size;

	size = 0;
	while (env_list)
	{
		env_list = env_list->next;
		size++;
	}
	return (size);
}

t_env			*envInit(char **env, t_free	*error_list)
{
	t_env	*env_list;
	t_env	*next;
	
	if (env && *env)
		env_list = newEnv(*env);
	else
		return ((t_env *)NULL);
	env++;
	next = env_list;
	while (env && *env)
	{
		next->next = newEnv(*env);
		next = next->next;
		env++;
	}
	error_list->env = true;
	return (env_list);
}

char	**t_env_to_array(t_env *env_list)
{
	char	**env_array;
	int 	i;
	
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