/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 01:29:04 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/07 14:58:42 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>

volatile int	g_signal = 0;

void	ft_signal_ctrlc(int signum)
{
	g_signal = signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal_quit(int signum)
{
	g_signal = signum;
	printf("\033[2D\033[0K");
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signal_heredoc(int signum)
{
	g_signal = signum;
	close(STDIN_FILENO);
}

void	init_signal(void)
{
	signal(SIGINT, &ft_signal_ctrlc);
	signal(SIGQUIT, &ft_signal_quit);
}
