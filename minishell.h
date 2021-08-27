/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 13:12:00 by tguimara          #+#    #+#             */
/*   Updated: 2021/08/27 09:36:43 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/include/libft.h"

typedef struct s_command {
	char				*command;
	char				**args;
	int					infile;
	int					outfile;
}	t_command;

void		handle_signals(void);
t_command	**commandList(char *buffer);
int			commandChecker(t_command *command);

#endif
