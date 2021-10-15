/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 09:47:07 by tguimara          #+#    #+#             */
/*   Updated: 2021/10/14 05:56:19 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

static int	init_minishell(t_config	**shell_config, char **env);
static char	**find_path(char **env, t_free	*error_list);

/*
	MINISHELL
	
	A função main() é responsável por:
	1. inicializar os parâmetros do shell - init_minishell()
	2. ler lista de comandos inseridas pelo usuário no stdin - readline()
	3. tokenizar os termos inseridos pelo usuário - tokenizer()
	4. construir as listas de comandos do pipeline
	5. fazer verificações de sintaxe - parser()
	6. executar o pipeline inserido - exec()
	
	Todas os parâmetros do shell são armazenados na struct t_config.

	Todos os parâmetros do pipeline (buffer do readline, lista de tokens e 
	list de comandos) são armanzenadas em uma struct t_pipeline.

	Tanto a t_config quanto o t_pipeline são declarados no minishell.h
*/
int	main(int argc, char **argv, char **env)
{
	char		*buffer;
	t_pipeline	*pipeline;

	handle_signals();
	if (!init_minishell(&g_shell_config, env))
		exit(-1);
	while (g_shell_config->should_continue)
	{
		printf("Should_continue: %d\n", g_shell_config->should_continue);
		pipeline = (t_pipeline *)malloc(sizeof(t_pipeline));
		if (!pipeline)
			exit(-1);
		buffer = readline("minishell>");
		if (buffer && buffer[0])
			add_history(buffer);
		pipeline->token_list = tokenizer(buffer, g_shell_config->env,
				g_shell_config->last_exit_status);
		free(buffer);
		buffer = NULL;
		pipeline->command_list = parser(&pipeline, g_shell_config->builtin_list,
				g_shell_config->path);
		exec(&pipeline, &g_shell_config);
		free_pipeline(&pipeline);
	}
	exit_minishell(g_shell_config);
	return (0);
}

/*
	static int	init_minishell(t_config	**shell_config, char **env)
	
	A função init_minishell() é responsável por inicializar e
	mallocar, quando necessário, as variáveis da struct t_config.
	A struct t_config é declarada no minishell.h
*/
static int	init_minishell(t_config	**shell_config, char **env)
{
	(*shell_config) = (t_config *)malloc(sizeof(t_config));
	if (!(*shell_config))
		return (-1);
	(*shell_config)->free_list = (t_free *)ft_calloc(sizeof(t_free *), 1);
	(*shell_config)->builtin_list = bultin_init((*shell_config)->free_list);
	(*shell_config)->env = env_init(env, (*shell_config)->free_list);
	(*shell_config)->path = find_path(env, (*shell_config)->free_list);
	if (!(*shell_config)->builtin_list || !(*shell_config)->env
		|| !(*shell_config)->path)
		return (-1);
	(*shell_config)->stdin = dup(1);
	(*shell_config)->stdout = dup(0);
	(*shell_config)->last_exit_status = -1;
	(*shell_config)->should_continue = true;
	return (1);
}

/*
	static char	**find_path(char **env)
	
	A função find_path() é responsável por alocar cada path descrito
	na variável PATH do char **env em um ponteiro de ponteiros.
	Esse alocação é realizada para facilitar a busca pelos paths
	declarados futuramente.
*/
static char	**find_path(char **env, t_free	*error_list)
{
	char	**path;

	while (*env)
	{
		if (!ft_strncmp(*env, "PATH", 4))
		{
			path = ft_split(*env, ':');
			if (!path)
				return (NULL);
			break ;
		}
		env++;
	}
	*path = ft_strtrim(*path, "PATH=");
	error_list->path = true;
	return (path);
}
