/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 13:12:00 by tguimara          #+#    #+#             */
/*   Updated: 2021/12/06 10:51:22 by tguimara         ###   ########.fr       */
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

# define EXIT_NUMBER		999

# include <stdbool.h>
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
	int					builtin;
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
	size_t				total_commands;
}	t_pipeline;

/*
	env path e bultinlist poderiam ser tornar hash table
	para facilitar o encontro de uma variável
*/
typedef struct s_env {
	char				**content;
	struct s_env		*next;
}	t_env;

typedef struct s_free {
	int					env;
	int					path;
	int					bultin;
	int					pipeline;
	int					token_list;
	int					command_list;
}	t_free;

typedef struct s_config {
	char				**builtin_list;
	char				**path;
	t_env				*env;
	int					stdin;
	int					stdout;
	int					last_exit_status;
	int					should_continue;
	t_free				*free_list;
}	t_config;

t_config	*g_shell_config;

// Minishell.c
int			main(int argc, char **argv, char **env);
static int	init_minishell(char **env);
static char	**find_path(char **env);

// general
void		handle_signals(void);
int			handle_exec_signals(void);
t_command	*parser(t_pipeline **pipeline, t_config *g_shell_config);
int			commandChecker(t_command *command);
void		exec(t_pipeline **pipeline);

// builtin
char		**bultin_init(void);
int			is_builtin(char *command, char **builtinList);
void		callBuiltin(t_command *command, t_env **env);
char		*my_pwd(void);
void		my_export(int total_args, char **args, t_env *env);
void		my_unset(int total_args, char **args, t_env *env);
void		my_env(int total_args, char **args, t_env *env);
void		my_cd(int total_args, char **args);
void		my_echo(char **args);
void		my_exit(t_pipeline **pipeline);

void		identifier_error(char *str, char ***temp_arg, int total_args);
void		no_equal_handler(char *str);

void		exit_minishell(void);

// exit
void		free_pipeline(t_pipeline **pipeline);

// env
// TODO: HA DUAS FUNCOES IS ENV
t_env		*env_init(char **env);
void		env_delete(t_env **env, t_env **env_before);
t_env		*get_last_env(t_env *env);
void		env_include(t_env **env_before, char *env);
void		env_print(t_env *env);
size_t		env_size(t_env	*env_list);
char		**t_env_to_array(t_env *env_list);
void		free_env_list(t_env *env_list);
int			is_env2(t_env *env, char *str);
t_env		*is_env(char *name, t_env *env);
char		*get_env_content(char *name, t_env *env);
void		update_env(char **temp_arg, t_env *env);

// tokenizer
t_token		*tokenizer(char *buffer, t_env *env, int exit_status);
int			token_type(char c);
int			expand_var(char *str, t_token **token, t_env *env, int exit_status);
int			read_string(char *str, t_token **token, t_env *env,
				int exit_status);
int			read_redir(char *str, t_token **token);
int			read_token(char *str, t_token **token);
size_t		read_pipe(t_token **token);

// utils
int			end_var_pos(char *str);

// parser
t_command	*init_command(t_token **token, char **builtin_list, t_env *env);

// free
void		free_pipeline(t_pipeline **pipeline);
void		free_config(void);

#endif
