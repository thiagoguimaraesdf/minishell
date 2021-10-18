/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 10:02:26 by tguimara          #+#    #+#             */
/*   Updated: 2021/10/18 12:01:13 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_pwd(void)
{
	char	*cur_dir;

	cur_dir = (char *)malloc(sizeof(char) * 100);
	if (!cur_dir)
		return ((char *) NULL);
	cur_dir = getcwd(cur_dir, 100);
	write(1, cur_dir, ft_strlen(cur_dir));
	write(1, "\n", 1);
	return (cur_dir);
}

void	my_echo(char **args)
{
	int	i;
	int	newline;

	newline = 1;
	i = 0;
	args++;
	if (args && !ft_strncmp(*args, "-n", ft_strlen(*args)))
	{
		newline = 0;
		i++;
	}
	while (args && args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		i++;
		if (args[i])
			write(1, " ", 1);
	}
	if (newline)
		write(1, "\n", 1);
}

void	my_cd(int total_args, char **args)
{
	int	chdir_return;

	if (!total_args)
		return ;
	else if (total_args > 1)
	{
		write(1, "-myshell: cd: too many arguments", 32);
		return ;
	}
	// INCLUIR -bash: cd: dsadas: No such file or directory CASO DIRETORIO NAO EXISTA
	if (args && args[1])
		chdir_return = chdir((const char *)args[1]);
}

void	my_env(int total_args, char **args, t_env *env)
{
	t_env	*temp_env;

	temp_env = env;
	if (total_args > 0)
		ft_printf("env: ‘%s’: No such file or directory", *args);
	while (temp_env)
	{
		env_print(temp_env);
		temp_env = temp_env->next;
	}
}

void	my_unset(int total_args, char **args, t_env *env)
{
	t_env	*last_env;
	t_env	*temp_env;

	if (!total_args)
		return ;
	args++;
	temp_env = env;
	while (args && *args)
	{
		while (temp_env)
		{
			if (!ft_strncmp(*args, temp_env->content[0], ft_strlen(*args)))
			{	
				printf("delete:%s\n", temp_env->content[0]);
				env_delete(&temp_env, &last_env);
				break ;
			}
			last_env = temp_env;
			temp_env = temp_env->next;
		}
		args++;
	}
}
