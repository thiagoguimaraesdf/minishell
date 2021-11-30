/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:06:59 by tguimara          #+#    #+#             */
/*   Updated: 2021/11/30 05:10:21 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**bultin_init(void)
{
	char		*builtins_string;
	char		**builtin_list;

	builtins_string = ft_strdup("echo,cd,pwd,export,unset,exit,env");
	builtin_list = ft_split(builtins_string, ',');
	if (!builtin_list)
		return ((char **) NULL);
	if (builtins_string)
		free(builtins_string);
	g_shell_config->free_list->bultin = true;
	return (builtin_list);
}

int	is_builtin(char *command, char **builtin_list)
{
	int		i;
	size_t	command_size;
	size_t	max_size;

	command_size = ft_strlen(command);
	max_size = command_size;
	i = 0;
	while (builtin_list && builtin_list[i])
	{
		if (ft_strlen(builtin_list[i]) > max_size)
			max_size = ft_strlen(builtin_list[i]);
		if (!ft_strncmp(command, builtin_list[i], max_size))
			return (1);
		if (max_size != command_size)
			max_size = command_size;
		i++;
	}
	return (0);
}

void	identifier_error(char *str, char ***temp_arg, int total_args)
{
	ft_printf("minishell: export: `%s': not a valid identifier\n", str);
	while (*temp_arg && **temp_arg)
		free(**temp_arg++);
	free(*(temp_arg - total_args));
	return ;
}

void	no_equal_handler(char *str)
{
	if (!ft_isalpha(str[0]))
		ft_printf("minishell: export: `%s': not a valid identifier\n", str);
}
