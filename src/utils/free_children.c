/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:26:53 by gcaptari          #+#    #+#             */
/*   Updated: 2024/08/30 10:50:09 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "tokens.h"

void	free_on_children(t_minishell *minishell)
{
	free_env();
	free_token(minishell->tokens);
	free_ast(&minishell->ast);
}
