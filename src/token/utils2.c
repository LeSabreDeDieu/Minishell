/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:51:41 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/15 16:18:59 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

int	is_in_quotes(const char *str, int index)
{
	int	single_quote;
	int	double_quote;
	int	i;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (i < index)
	{
		if (str[i] == '\'')
			single_quote = !single_quote;
		else if (str[i] == '\"')
			double_quote = !double_quote;
		i++;
	}
	return (single_quote || double_quote);
}

int	is_in_subshell(const char *str, int index)
{
	int	subshell_count;
	int	i;

	subshell_count = 0;
	i = 0;
	while (i < index)
	{
		if (str[i] == '(')
			subshell_count++;
		else if (str[i] == ')')
			subshell_count--;
		i++;
	}
	return (subshell_count > 0);
}

bool	is_space_in_quotes(char *str)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote = !quote;
		if (str[i] == ' ' && quote)
			return (1);
		++i;
	}
	return (0);
}

void	token_syntax_error(char *str)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": syntax error near unexpected token « ",
		STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(" »", STDERR_FILENO);
}

void	token_not_close(char *str)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": not closed « ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(" »", STDERR_FILENO);
}
