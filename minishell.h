/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 13:12:00 by tguimara          #+#    #+#             */
/*   Updated: 2021/09/02 15:31:37 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/include/libft.h"

typedef struct s_command {
	char				*command;
	char				**args;
	char				*redirection_in;
	char				*redirection_out;
	char				**filenames;
}	t_command;

// static char *path;

// path = ft_strdup("/bin");

void		handle_signals(void);
t_command	**commandList(char *buffer);
int			commandChecker(t_command *command);
int			commandExec(t_command *command, char **builtinList);

#endif
