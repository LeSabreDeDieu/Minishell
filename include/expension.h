/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:16:42 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/17 16:18:49 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPENSION_H
# define EXPENSION_H

# include <dirent.h>

# include "ast.h"
# include "minishell.h"
# include "dlist.h"

typedef struct s_ast_value			t_ast_value;
typedef struct s_redirection_list	t_redirection_list;
typedef struct s_dlist				t_dlist;

typedef struct s_pos
{
	int	i;
	int	j;
}		t_pos;

void			to_dequote(t_ast_value *value);
char			*dequote(char *str);
int				expend(t_minishell *shell_data, t_ast_value *value);

// Utils
int				expend_variable_from_env(t_ast_value *value, int *i, int j,
					bool is_quoted);
bool			is_in_dquote(char *c, bool is_in_quote);
void			get_pid_as_string(char *pid_str);
bool			wildcard_in_quote(char *str);
int				pos_next_quote(char *str, char quote);
int				pos_next_quote2(t_minishell *shell_data, char *str, char quote);
char			*get_end(char *str);
int				find_match(const char *pattern, const char *str);
int				match(const char *pattern, const char *str);
int				ft_realloc_and_split(t_dlist *stack, t_ast_value *value, int i);
void			wildcard_error_message(const char *pattern);
void			dequote_delimiter(t_redirection_list *redir_list);
bool			is_dollar_allone(t_ast_value *value, t_pos *pos);

void			add_file_wildcard(t_dlist **stack, char *pattern,
					struct dirent *entry, char *repo);
char			*get_copy_pattern(const char *pattern, char **pattern_copy);

void			expend_last_status(t_minishell *shell_data, t_ast_value *value,
					t_pos *pos);
void			expend_tild(t_minishell *shell_data, t_ast_value *value,
					t_pos *pos);
int				expend_wildcard(t_minishell *shell_data, char *argv);

char			**ft_split_not_in_quote(char *str);
void			split_stack_elements(t_dlist **stack);
bool			char_in_quote(char *str, char c);

const char		*find_space(const char *input);

#endif
