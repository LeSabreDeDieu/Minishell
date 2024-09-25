/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:16:42 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/25 10:29:12 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPENSION_H
# define EXPENSION_H

# include "ast.h"
# include "minishell.h"

typedef struct s_ast_value			t_ast_value;
typedef struct s_redirection_list	t_redirection_list;

typedef struct s_pos
{
	int						i;
	int						j;
}							t_pos;

typedef struct s_wildcard
{
	char					*str;
	struct s_wildcard		*next;
}							t_wildcard;

void						to_dequote(t_ast_value *value);
char						*dequote(char *str);
int							expend_wildcard(char ***argv, int *argc);
int							expend(t_minishell *shell_data, t_ast_value *value);

// Utils
void						expend_variable_from_env(t_ast_value *value, int i,
								int *j);
bool						is_in_dquote(char c, bool is_in_quote);
void						get_pid_as_string(char *pid_str);
bool						wildcard_in_quote(char *str);
int							pos_next_quote(char *str);
char						*get_end(char *str);
int							find_match(const char *pattern, const char *str);
int							match(const char *pattern, const char *str);
void						ft_realloc_and_split(t_ast_value *value, int i);
void						wildcard_error_message(const char *pattern);
void						dequote_delimiter(t_redirection_list *redir_list);

// Wildcard
t_wildcard					*new_wildcard(char *str);
int							wildcard_len(t_wildcard *wildcard);
void						add_wildcard(t_wildcard **wildcard,
								t_wildcard *new);
void						free_wildcard(t_wildcard **wildcard);
void						add_file_wildcard(t_wildcard **wildcard,
								char *pattern, struct dirent *entry,
								char *repo);
char						*get_copy_pattern(const char *pattern,
								char **pattern_copy);

#endif