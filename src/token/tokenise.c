/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:34:55 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/03 09:34:55 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "tokens.h"

static void	tokenise_word(char **str)
{
	t_token	*token_tmp;
	char	*tmp;

	tmp = get_word(str);
	if (!tmp)
		return ;
	token_tmp = create_token(tmp, TOKEN_WORD);
	if (!token_tmp)
		return (free_token());
	free(tmp);
	add_token(token_tmp);
}

static void	tokenise_special_char(char *str, int token)
{
	t_token	*token_tmp;

	token_tmp = create_token(str, token);
	if (!token_tmp)
		return (free_token());
	add_token(token_tmp);
}

static void	tokenise_redirect_char(char **str)
{
	t_token	*token_tmp;
	char	*tmp;

	if (**str == '<')
	{
		if (*(*str + 1) == '<')
			tmp = "<<";
		else
			tmp = "<";
	}
	else
	{
		if (*(*str + 1) == '>')
			tmp = ">>";
		else
			tmp = ">";
	}
	*str += 1;
	if (**str == '>' || **str == '<')
		*str += 1;
	token_tmp = create_token(tmp, TOKEN_REDIRECTION);
	if (!token_tmp)
		return (free_token());
	add_token(token_tmp);
}

static void	tokenise2(char **str, t_token_config *conf)
{
	if (**str == conf->redirection[0] || **str == conf->redirection[1])
		tokenise_redirect_char(str);
	else if (**str == conf->variable)
	{
		tokenise_special_char("$", TOKEN_VARIABLE);
		*str += 1;
		return ;
	}
	tokenise_word(str);
	*str += 1;
}

char	*get_right_end(char *str)
{
	int		count;
	char	*tmp;

	count = 0;
	tmp = str;
	while (*tmp)
	{
		if (*tmp == '(')
			++count;
		if (*tmp == ')')
			--count;
		++tmp;
		if (count == 0)
			break ;
	}
	return (tmp);
}

void	tokenise(char **str, t_token_config *conf, bool is_and_or)
{
	char	*tmp;

	if (**str == conf->double_quote)
	{
		tmp = ft_substr(*str, 0, (ft_strchr(*str + 1, '"') - *str) + 1);
		if (!tmp)
			return ;
		tokenise_special_char(tmp, TOKEN_DOUBLE_QUOTE);
		*str += ft_strlen(tmp);
		free(tmp);
	}
	else if (**str == conf->simple_quote)
	{
		tmp = ft_substr(*str, 0, (ft_strchr(*str + 1, '\'') - *str) + 1);
		if (!tmp)
			return ;
		tokenise_special_char(tmp, TOKEN_SIMPLE_QUOTE);
		*str += ft_strlen(tmp);
		free(tmp);
		return ;
	}
	else if (**str == conf->subshell_start)
	{
		tmp = ft_substr(*str, 0, (get_right_end(*str) - *str));
		if (!tmp)
			return ;
		tokenise_special_char(tmp, TOKEN_SUBSHELL);
		*str += ft_strlen(tmp);
		free(tmp);
	}
	else if (is_and_or && ft_strchr(*str, '|') && ft_strstr(*str, "||") == NULL)
	{
		tokenise_special_char(*str, TOKEN_SUBSHELL);
		*str += ft_strlen(*str);
	}
	else if (**str == conf->pipe)
	{
		tokenise_special_char("|", TOKEN_PIPE);
		*str += 1;
	}
	else
		tokenise2(str, conf);
}
