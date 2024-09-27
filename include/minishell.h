/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:45:02 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/26 10:00:06 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// pour readline
# include <readline/readline.h>
// pour rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay,
// add_history
# include <readline/history.h>
// pour printf, perror
# include <stdio.h>
// pour malloc, free, exit, getenv
# include <stdlib.h>
// pour write, access, read, close,
// fork, getcwd, chdir, unlink, execve,
// dup, dup2, pipe, isatty, ttyname, ttyslot
# include <unistd.h>
// pour open
# include <fcntl.h>
// pour fork, wait, waitpid, wait3, wait4, stat, lstat, fstat
# include <sys/types.h>
// pour wait, waitpid, wait3, wait4
# include <sys/wait.h>
// pour signal, sigaction, sigemptyset, sigaddset, kill
# include <signal.h>
// pour stat, lstat, fstat
# include <sys/stat.h>
// pour opendir, readdir, closedir
# include <dirent.h>
// pour strerror
# include <string.h>
// pour ioctl
# include <sys/ioctl.h>
// pour tcsetattr, tcgetattr
# include <termios.h>
// pour tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <curses.h>
# include <term.h>

# include "env.h"
# include "ast.h"
# include "command.h"
# include "tokens.h"
# include "libft.h"
# include "utils.h"
# include "color.h"
# include "expension.h"
# include "ms_error.h"
# include "stack.h"

extern volatile int		g_signal;

typedef struct s_ast	t_ast;
typedef struct s_tokens	t_tokens;

# define SHELL_NAME "SanicShell"
# define HISTORY_FILE "/.sanicshell_history"

typedef struct s_data_minishell
{
	char		*username;
	char		*path;
	char		*home;
}				t_data_minishell;

typedef struct s_minishell
{
	t_data_minishell	data;
	t_ast				*ast;
	t_tokens			*tokens;
	int					current_status;
	bool				is_here_doc;
	t_stack				*stack;
}				t_minishell;

char	*create_display(t_minishell *shell_data);
char	*rl_gets(t_data_minishell *data, char *prompt);
int		traitement(t_minishell *data, char *prompt);
void	set_env_from_void(void);
char	*get_uname(void);

//HISTORIQUE
int		add_history_file(t_data_minishell *data, char *line);
int		read_history_from_file(t_data_minishell *data);
int		clear_history_file(t_data_minishell *data);

//UTILS
void	print_welcome(void);
int		open_all_here_doc(t_minishell *minishell, t_ast *ast, int itterdoc);
int		expend_and_dequote(t_minishell *data, t_ast *ast);

//SIGNAL
void	init_signal(void);
void	ft_signal_ctrlc(int signum);
void	ft_signal_quit(int signum);
void	ft_signal_heredoc(int signum);

#endif
