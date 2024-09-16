/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:45:02 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/16 16:46:40 by sgabsi           ###   ########.fr       */
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
# include "ast.h"
# include "command.h"
# include "tokens.h"
# include "libft.h"
# include "utils.h"

extern int g_signal;

typedef struct s_ast	t_ast;
typedef struct s_tokens	t_tokens;

# define SHELL_NAME "SanicShell"

typedef struct s_data_minishell
{
	char		*username;
	char		*path;
}				t_data_minishell;

typedef struct s_minishell
{
	t_data_minishell	data;
	t_ast				*ast;
	t_tokens			*tokens;
	int					current_status;
}				t_minishell;

char	*rl_gets( void );
int		traitement(t_minishell *data, char *prompt);
void	set_env_from_void(void);
void	init_signal(void);

#endif
