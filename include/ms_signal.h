/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:20:16 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/10 14:35:04 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNAL_H
# define MS_SIGNAL_H

# include <signal.h>

extern volatile int		g_signal;

void	init_signal(void);
void	ft_signal_ctrlc(int signum);
void	ft_signal_quit(int signum);
void	ft_signal_heredoc(int signum);
void	ft_signal_child(int signum);

#endif