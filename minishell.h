/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 13:12:00 by tguimara          #+#    #+#             */
/*   Updated: 2021/09/22 15:15:39 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define IS_INVALID			-1
# define IS_COMMON			0
# define IS_PIPE			1
# define IS_VAR				2
# define IS_QUOTE			3
# define IS_SINGLE_QUOTE	4
# define IS_SPACE			5
# define IS_UNSPECIFIED		6
# define IS_REDIR			20

# define IS_REDIR_IN		21
# define IS_REDIR_OUT		22
# define IS_REDIR_IN_2		23
# define IS_REDIR_OUT_2		24

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft/include/libft.h"
# include "libft/include/ft_printf.h"

typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_command {
	char				*command;
	int 				builtin;
	char				*exec_path;
	char				**args;
	int					total_args;
	char				**redirection_in;
	char				**redirection_out;
	int					has_pipe;
	struct s_command	*next;
}	t_command;

typedef struct s_pipeline {
	t_token				*token_list;
	t_command			*command_list;
	size_t 				total_commands;
}	t_pipeline;

/*
	env path e bultinlist poderiam ser tornar hash table para facilitar o encontro de uma variável
*/
typedef struct s_env {
	char				**content;
	struct s_env		*next;
}	t_env;

typedef struct s_config {
	char				**builtin_list;
	char 				**path;
	t_env				*env;
	int					stdin;
	int					stdout;
	int					last_exit_status;
}	t_config;

t_config	*shell_config;

void		handle_signals(void);
t_command	*parser(t_pipeline **pipeline, char **builtin_list, char **path);
int			commandChecker(t_command *command);
void		exec(t_pipeline **pipeline, t_config **shell_config);

// builtin

char 		**bultinInit();
int			isBuiltin(char *command, char **builtinList);
void		callBuiltin(t_command *command, t_env **env);
char		*myPwd(void);
void		myExport(int total_args, char **args, t_env **env);
void		myUnset(int total_args, char **args, t_env **env);
void		myEnv(int total_args, char **args, t_env *env);
void		myCd(int total_args, char **args);
void		myEcho(char **args);
void		myExit(t_config **shell_config, t_pipeline **pipeline);

// exit
void	free_pipeline(t_pipeline **pipeline);
// env

t_env		*envInit(char **env);
void		envDelete(t_env **env, t_env **env_before);
t_env		*getLastEnv(t_env *env);
void 		envInclude(t_env **env_before, char *env);
void 		envPrint(t_env *env);
size_t 		env_size(t_env	*env_list);
char		**t_env_to_array(t_env *env_list);
void		free_env_list(t_env **env_list);

// tokenizer

t_token		*tokenizer(char *buffer, t_env *env, int exit_status);

#endif
