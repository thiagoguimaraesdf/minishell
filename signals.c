/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 13:11:29 by tguimara          #+#    #+#             */
/*   Updated: 2021/11/29 15:26:14 by tguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "minishell.h"

static void	handle_interrupt(int sig_num)
{
	(void)sig_num;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

static void	fork_int(int signal)
{
	(void)signal;
	g_shell_config->last_exit_status = 130;
	write(1, "\n", 1);
}

static void	fork_quit(int signal)
{
	(void)signal;
	g_shell_config->last_exit_status = 131;
	ft_printf("Quit\n");
}

void	handle_signals(void)
{
	signal(SIGINT, handle_interrupt);
	signal(SIGQUIT, SIG_IGN);
	return ;
}

void	handle_exec_signals(void)
{
	signal(SIGINT, fork_int);
	signal(SIGQUIT, fork_quit);
	return ;
}
