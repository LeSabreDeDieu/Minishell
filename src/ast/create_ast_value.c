/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:55:12 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/07 15:59:22 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	create_redirection(t_redirection *redir, char *filename,
		t_type_redirection flag)
{
	redir->filename = ft_strdup(filename);
	redir->fd = -1;
	redir->flag = flag;
}

int	get_type_redirection(char *str)
{
	int	type;

	type = FAILURE;
	if (ft_strncmp(str, "<<", 2) == 0)
		type = HERE_DOC;
	else if (ft_strncmp(str, ">>", 2) == 0)
		type = APPEND;
	else if (ft_strncmp(str, "<", 1) == 0)
		type = READ;
	else if (ft_strncmp(str, ">", 1) == 0)
		type = WRITE;
	return (type);
}

int	add_list_redirection(t_redirection_list **list, t_token *type, char *file)
{
	t_redirection_list	*current;

	if (!type)
		return (FAILURE);
	if (!file)
		return (FAILURE);
	if (!*list)
	{
		*list = ft_calloc(1, sizeof(t_redirection_list));
		if (!*list)
			return (FAILURE);
		create_redirection(&(*list)->redirection, file,
			get_type_redirection(type->value));
		return (SUCCESS);
	}
	current = (*list);
	while (current->next)
		current = current->next;
	current->next = ft_calloc(1, sizeof(t_redirection_list));
	if (!current->next)
		return (FAILURE);
	create_redirection(&current->next->redirection, file,
		get_type_redirection(type->value));
	return (SUCCESS);
}

static int	create_ast_value_word(t_ast_value *value, t_token_list **tokens)
{
	t_token_list	*current;

	value->pid = -1;
	value->fd_in = -1;
	value->fd_out = -1;
	current = *tokens;
	if (current->token->type != TOKEN_WORD
		&& current->token->type != TOKEN_REDIRECTION
		&& !is_quote(current->token))
		return (FAILURE);
	if (create_redirection_list(&value, &current) == FAILURE)
		return (FAILURE);
	if (count_nb_arg(&value, &current) == FAILURE)
		return (FAILURE);
	if (value->argc != 0)
	{
		value->argv = ft_calloc(value->argc + 1, sizeof(char *));
		if (!value->argv)
			return (FAILURE);
		if (add_argv_value(&value, &current) == FAILURE)
			return (FAILURE);
		value->name = value->argv[0];
	}
	*tokens = current;
	return (SUCCESS);
}

int	create_ast_value(t_ast_value *value, t_token_list **tokens)
{
	t_token_list	*current;

	if (!tokens || !*tokens)
		return (FAILURE);
	current = *tokens;
	if (current->token->type == TOKEN_WORD || is_quote(current->token)
		|| current->token->type == TOKEN_REDIRECTION)
		return (create_ast_value_word(value, tokens));
	else if (current->token->type == TOKEN_SUBSHELL)
	{
		value->name = current->token->value;
		current = current->next;
		while (current && current->token->type == TOKEN_REDIRECTION)
		{
			if (current->next && add_list_redirection(&value->redirections,
					current->token, current->next->token->value) == FAILURE)
				return (FAILURE);
			current = current->next->next;
		}
	}
	if (!current)
		*tokens = NULL;
	else
		*tokens = current;
	return (SUCCESS);
}
