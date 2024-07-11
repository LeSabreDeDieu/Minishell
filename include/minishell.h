/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:45:02 by sgabsi            #+#    #+#             */
/*   Updated: 2024/07/10 17:27:23 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>  // pour readline
# include <readline/history.h>   // pour rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
# include <stdio.h>              // pour printf, perror
# include <stdlib.h>             // pour malloc, free, exit, getenv
# include <unistd.h>             // pour write, access, read, close, fork, getcwd, chdir, unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot
# include <fcntl.h>              // pour open
# include <sys/types.h>          // pour fork, wait, waitpid, wait3, wait4, stat, lstat, fstat
# include <sys/wait.h>           // pour wait, waitpid, wait3, wait4
# include <signal.h>             // pour signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h>           // pour stat, lstat, fstat
# include <dirent.h>             // pour opendir, readdir, closedir
# include <string.h>             // pour strerror
# include <sys/ioctl.h>          // pour ioctl
# include <termios.h>            // pour tcsetattr, tcgetattr
# include <curses.h>             // pour tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <term.h>               // pour tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

# include "env.h"
# include "command.h"
# include "tokens.h"
# include "libft.h"
# include "utils.h"

typedef struct s_minishell
{
	t_tokens	*tokens;
}				t_minishell;

char	*rl_gets( void );


#endif