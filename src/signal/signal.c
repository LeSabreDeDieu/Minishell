/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 01:29:04 by gcaptari          #+#    #+#             */
/*   Updated: 2024/09/18 17:56:40 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_signal = 0;

void	ft_signal_ctrlc(int signum)
{
	g_signal = signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
}

void	ft_signal_quit(int signum)
{
	g_signal = signum;
	rl_on_new_line();
	rl_redisplay();
}

void	init_signal(void)
{
	signal(SIGINT, &ft_signal_ctrlc);
	signal(SIGQUIT, &ft_signal_quit);
}
