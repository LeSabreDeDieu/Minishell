/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:55:12 by sgabsi            #+#    #+#             */
/*   Updated: 2024/07/25 18:22:24 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	create_redirection(t_redirection *redir,
						char *filename,
						t_type_redirection flag)
{
	redir->filename = filename;
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

int	add_list_redirection(t_redirection_list	**list,
							t_token *type,
							char *file)
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
	t_token_list		*current;
	t_token_list		*tmp;
	int					i;

	current = *tokens;
	if (current->token->type != TOKEN_WORD
		&& current->token->type != TOKEN_REDIRECTION)
		return (FAILURE);
	while (current && current->token->type == TOKEN_REDIRECTION)
	{
		if (current->next && add_list_redirection(&value->redirections, current->token,
				current->next->token->value) == FAILURE)
			return (FAILURE);
		current = current->next->next;
	}
	i = 0;
	tmp = current;
	while (tmp && tmp->token->type == TOKEN_WORD)
	{
		value->argc++;
		tmp = tmp->next;
	}
	if (value->argc != 0)
	{
		value->argv = ft_calloc(value->argc + 1, sizeof(char *));
		if (!value->argv)
			return (FAILURE);
		while (current && current->token->type == TOKEN_WORD)
		{
			value->argv[i++] = current->token->value;
			current = current->next;
		}
		value->name = value->argv[0];
	}
	while (current && current->token && current->token->type == TOKEN_REDIRECTION)
	{
		if (current->next && add_list_redirection(&value->redirections, current->token,
				current->next->token->value) == FAILURE)
			return (FAILURE);
		current = current->next->next;
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
	ft_bzero(value, sizeof(*value));
	if (current->token->type == TOKEN_WORD
		|| current->token->type == TOKEN_REDIRECTION)
		return (create_ast_value_word(value, tokens));
	else if (current->token->type == TOKEN_SUBSHELL)
	{
		value->name = current->token->value;
		current = current->next;
		while (current && current->token->type == TOKEN_REDIRECTION)
		{
			if (current->next && add_list_redirection(&value->redirections, current->token,
					current->next->token->value) == FAILURE)
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
