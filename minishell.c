/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 09:47:07 by tguimara          #+#    #+#             */
/*   Updated: 2021/11/29 10:43:55 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

static int	init_minishell(char **env);
static char	**find_path(char **env);
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
	if (!init_minishell(env))
		exit(-1);
	while (g_shell_config->last_exit_status != 59136)
	{
		pipeline = (t_pipeline *)malloc(sizeof(t_pipeline));
		buffer = readline("minishell>");
		if (!pipeline || !buffer)
			exit(-1);
		if (buffer && buffer[0])
			add_history(buffer);
		pipeline->token_list = tokenizer(buffer, g_shell_config->env,
				g_shell_config->last_exit_status);
		free(buffer);
		buffer = NULL;
		pipeline->command_list = parser(&pipeline, g_shell_config);
		exec(&pipeline);
		// free_pipeline(&pipeline);
		//printf("Exit_status: %d\n", g_shell_config->last_exit_status);
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
static int	init_minishell(char **env)
{
	g_shell_config = (t_config *)malloc(sizeof(t_config));
	if (!(g_shell_config))
		return (-1);
	g_shell_config->free_list = (t_free *)ft_calloc(sizeof(t_free *), 1);
	g_shell_config->builtin_list = bultin_init();
	g_shell_config->env = env_init(env);
	g_shell_config->path = find_path(env);
	if (!g_shell_config->builtin_list || !g_shell_config->env
		|| !g_shell_config->path)
		return (-1);
	g_shell_config->stdin = dup(1);
	g_shell_config->stdout = dup(0);
	g_shell_config->last_exit_status = -1;
	g_shell_config->should_continue = true;
	return (1);
}

/*
	static char	**find_path(char **env)
	
	A função find_path() é responsável por alocar cada path descrito
	na variável PATH do char **env em um ponteiro de ponteiros.
	Esse alocação é realizada para facilitar a busca pelos paths
	declarados futuramente.
*/
static char	**find_path(char **env)
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
	g_shell_config->free_list->path = true;
	return (path);
}
